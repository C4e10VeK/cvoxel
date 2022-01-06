#include "window.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Window mainWindow;

static void _errorWndCallback(int code, const char* log)
{
	printf("%i::%s", code, log);
}

static void _framebufferCallback(GLFWwindow* wnd, int width, int height)
{
	(void) wnd;
	glViewport(0, 0, width, height);
	mainWindow.size = (vec2s){{width, height}};
}

static void _keyboardCallback(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
	(void) wnd;
	(void) scancode;
	(void) mods;

	if (key < 0) return;

	switch (action)
	{
		case GLFW_PRESS:
			mainWindow.keyboardBtns[key].pressed = true;
			break;
		case GLFW_RELEASE:
			mainWindow.keyboardBtns[key].pressed = false;
			break;
		default:
			break;
	}
}

static void _mouseBtnCallback(GLFWwindow* wnd, int btn, int action, int mode)
{
	(void) wnd;
	(void) mode;

	if (btn < 0) return;

	switch (action)
	{
		case GLFW_PRESS:
			mainWindow.mouse.btn[btn].pressed = true;
			break;
		case GLFW_RELEASE:
			mainWindow.mouse.btn[btn].pressed = false;
			break;
		default:
			break;
	}
}

static void _cursorPosCallback(GLFWwindow* wnd, double x, double y)
{
	(void) wnd;

	vec2s p = (vec2s){{x, y}};

	mainWindow.mouse.delta = (vec2s){{
		p.x -  mainWindow.mouse.pos.x,  
		mainWindow.mouse.pos.y - p.y  
	}};

	mainWindow.mouse.pos = p;

	mainWindow.cursorUpdate();
}

void createWindow(int width, int height, const char *title, 
	WndFunc load, 
	WndFunc update, 
	WndFunc render, 
	WndFunc destroy,
	WndFunc cursorUpd)
{
	glfwSetErrorCallback(_errorWndCallback);
	if (!glfwInit()) 
	{
		fprintf(stderr, "error in glfwInit(), %s", __FUNCTION__);
		exit(1);
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mainWindow._glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!mainWindow._glfwWindow) 
	{
		fprintf(stderr, "error in glfwCrreateWindo(), %s", __FUNCTION__);
		glfwTerminate();
		exit(0);
	}

	glfwMakeContextCurrent(mainWindow._glfwWindow);

	if (!gladLoadGL(glfwGetProcAddress)) 
	{
		fprintf(stderr, "error in gladLoadGL(), %s", __FUNCTION__);
		glfwDestroyWindow(mainWindow._glfwWindow);
		glfwTerminate();
		exit(1);
	}

	mainWindow.size         = (vec2s){{width, height}};
	mainWindow.mouse.pos    = (vec2s){{width/2.0f, height/2.0f}};
	mainWindow.load         = load;
	mainWindow.update       = update;
	mainWindow.render       = render;
	mainWindow.destroy      = destroy;
	mainWindow.cursorUpdate = cursorUpd;

	// glfwSetInputMode(mainWindow._glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(mainWindow._glfwWindow, _framebufferCallback);
	glfwSetKeyCallback(mainWindow._glfwWindow, _keyboardCallback);
	glfwSetMouseButtonCallback(mainWindow._glfwWindow, _mouseBtnCallback);
	glfwSetCursorPosCallback(mainWindow._glfwWindow, _cursorPosCallback);
}

void runWindow()
{
	mainWindow.load();
	
	while (!glfwWindowShouldClose(mainWindow._glfwWindow)) 
	{
		mainWindow.currentTime = glfwGetTime();
		mainWindow.deltaTime = mainWindow.currentTime - mainWindow.lastTime;
		mainWindow.lastTime = mainWindow.currentTime;

		mainWindow.update();
		mainWindow.render();

		glfwSwapBuffers(mainWindow._glfwWindow);
		glfwPollEvents();
	}

	mainWindow.destroy();

	glfwDestroyWindow(mainWindow._glfwWindow);
	glfwTerminate();
}

