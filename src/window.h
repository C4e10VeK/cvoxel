#ifndef CVOXEL_WINDOW_H
#define CVOXEL_WINDOW_H

#include <stdbool.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/types-struct.h>


typedef void (*WndFunc)();

typedef struct
{
    bool pressed;
} Button;

typedef struct
{
    Button btn[GLFW_MOUSE_BUTTON_LAST];
    vec2s pos, delta;
} Mouse;

typedef struct
{
    GLFWwindow* _glfwWindow;
    vec2s size;

    float deltaTime, currentTime, lastTime;

    Button keyboardBtns[GLFW_KEY_LAST];
    Mouse mouse;

    WndFunc load, update, render, destroy, cursorUpdate;
} Window;

extern Window mainWindow;

void createWindow(int width, int height, const char* title,
    WndFunc load, WndFunc update, WndFunc render, WndFunc destroy
);

void runWindow();

#endif
