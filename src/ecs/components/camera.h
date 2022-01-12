#ifndef CVOXEL_CAMERA_C_H
#define CVOXEL_CAMERA_C_H

#include <cglm/types-struct.h>

typedef struct
{
	mat4s projection;
	mat4s view;
	float scale;
} Camera;

#endif