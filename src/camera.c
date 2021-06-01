#include "camera.h"
#include "window.h"
#include <cglm/struct/vec3.h>
#include <cglm/struct/mat4.h>
#include <cglm/struct/cam.h>

Camera createCamera(vec3s pos, float fov, float sensivity)
{
    Camera cam = {
        .aspect = (mainWindow.size.x / mainWindow.size.y),
        .fov = fov,
        .sensivity = sensivity,
        .yaw = -90.0f,
        .pitch = 0.0f,
        .pos = pos
    };

    cam.front = (vec3s){{0.0f, 0.0f, -1.0f}};
    cam.up = (vec3s){{0.0f, 1.0f, 0.0f}};

    cam.proj = glms_perspective(cam.fov, cam.aspect, 0.1f, 100.0f);

    cam.view = glms_lookat(cam.pos, glms_vec3_add(cam.pos, cam.front), cam.up);

    return cam;
}

void cameraVectorUpdate(Camera *cam)
{
    cam->yaw   += mainWindow.mouse.delta.x * cam->sensivity;
    cam->pitch += mainWindow.mouse.delta.y * cam->sensivity;
    cam->pitch =  glm_clamp(cam->pitch, -89.0f, 89.0f);

    cam->front = (vec3s){{
        cosf(glm_rad(cam->yaw)) * cosf(glm_rad(cam->pitch)),
        sinf(glm_rad(cam->pitch)),
        sinf(glm_rad(cam->yaw)) * cosf(glm_rad(cam->pitch))
    }};

    glms_vec3_norm(cam->front);
    cam->right = glms_vec3_crossn(cam->front, cam->up);
}
