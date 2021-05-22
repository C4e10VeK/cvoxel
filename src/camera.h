#ifndef CVOXEL_CAMERA_H
#define CVOXEL_CAMERA_H

#include <cglm/types-struct.h>

typedef struct
{
    float fov, yaw, pitch, aspect;
    vec3s pos, front, up, right;
    mat4s proj, view;
} Camera;

Camera createCamera(vec3s pos, float fov);

void cameraVectorUpdate(Camera* cam);

#endif

