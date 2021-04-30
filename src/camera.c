#include "camera.h"
#include <cglm/cglm.h>
#include "utils/vec3s.h"

Camera createCamera(vec3s pos, float aspect, float fov)
{
    Camera cam = {
        .aspect = aspect,
        .fov = fov,
        .yaw = -90.0f,
        .pitch = 0.0f,
        .pos = pos
    };

    cam.front = (vec3s){{0.0f, 0.0f, -1.0f}};
    cam.up = (vec3s){{0.0f, 1.0f, 0.0f}};

    glm_perspective(cam.fov, cam.aspect, 0.1f, 100.0f, cam.proj.raw);

    glm_lookat(cam.pos.raw, vec3_add(cam.pos, cam.front).raw, cam.up.raw, cam.view.raw);

    return cam;
}