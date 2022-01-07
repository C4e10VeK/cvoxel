#ifndef CVOXEL_WINDOW_H
#define CVOXEL_WINDOW_H

#include <stdbool.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../../utils/types.h"
#include "input.h"

typedef struct Window
{
	bool keys[GLFW_KEY_LAST + 1];
	Mouse mouse;

	GLFWwindow *raw;
	i32 width, height;
} Window;

typedef struct
{
	i32 width, height;
	bool resizable;
} WindowParams;

bool windowInit(Window *wnd, WindowParams params, const char *title);

bool windowIsClosed(Window *wnd);

void windowClose(Window *wnd);

void windowPollEvents();

void windowSwapBuffers(Window *wnd);

void windowDestroy(Window *wnd);

#endif // CVOXEL_WINDOW_H