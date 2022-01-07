#ifndef CVOXEL_INPUT_H
#define CVOXEL_INPUT_H

#include <stdbool.h>
#include "../../utils/types.h"

typedef struct
{
	// array[GLFW_MOUSE_BUTTON_LAST + 1]
	bool buttons[8];
	float x, y;
	float deltaX, deltaY;
} Mouse;

#endif // CVOXEL_INPUT_H