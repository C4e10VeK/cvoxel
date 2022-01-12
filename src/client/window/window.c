#include "window.h"

#include <glad/gl.h>

#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "../../utils/macro.h"
#include "../../utils/vmath.h"

static void _keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	UNUSED(scancode);
	UNUSED(mods);

	if (key < 0) return;

	Window *wnd = (Window *)glfwGetWindowUserPointer(window);

	switch (action)
	{
	case GLFW_PRESS:
		wnd->keys[key] = true;
		break;
	case GLFW_RELEASE:
		wnd->keys[key] = false;
		break;
	default:
		break;
	}

}

static void _resizeCallback(GLFWwindow *window, int width, int height)
{
	Window *wnd = (Window *)glfwGetWindowUserPointer(window);	
	wnd->width = width;
	wnd->height = height;
}

static void _cursorPosCallback(GLFWwindow *window, double x, double y)
{
	Window *wnd = (Window *)glfwGetWindowUserPointer(window);

	wnd->mouse.deltaX = x - wnd->mouse.x;
	wnd->mouse.deltaY = y - wnd->mouse.y;

	wnd->mouse.deltaX = CLAMP(wnd->mouse.deltaX, 0.0f, 100.0f);
	wnd->mouse.deltaY = CLAMP(wnd->mouse.deltaY, 0.0f, 100.0f);

	wnd->mouse.x = x;
	wnd->mouse.y = y;
}

static bool _windowInitGlad(const Window *wnd)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(wnd->raw);
	
	return gladLoadGL(glfwGetProcAddress);
}

bool windowInit(Window *wnd, WindowParams params, const char *title)
{
	if (!wnd)
		return false;

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_RESIZABLE, params.resizable);

	wnd->raw = glfwCreateWindow(params.width, params.height, title, NULL, NULL);

	if (!wnd->raw)
		return false;

	wnd->width = params.width;
	wnd->height = params.height;

	memset(wnd->keys, 0, GLFW_KEY_LAST + 1);
	memset(wnd->mouse.buttons, 0, GLFW_MOUSE_BUTTON_LAST + 1);

	glfwSetWindowUserPointer(wnd->raw, wnd);

	glfwSetKeyCallback(wnd->raw, _keyCallback);
	glfwSetFramebufferSizeCallback(wnd->raw, _resizeCallback);
	glfwSetCursorPosCallback(wnd->raw, _cursorPosCallback);

	return _windowInitGlad(wnd);
}

bool windowIsClosed(Window *wnd)
{
	return glfwWindowShouldClose(wnd->raw);
}

void windowClose(Window *wnd)
{
	glfwSetWindowShouldClose(wnd->raw, true);
}

void windowPollEvents()
{
	glfwPollEvents();
}

void windowSwapBuffers(Window *wnd)
{
	glfwSwapBuffers(wnd->raw);
}

void windowDestroy(Window *wnd)
{
	assert(wnd);
	glfwDestroyWindow(wnd->raw);
	glfwTerminate();	
}
