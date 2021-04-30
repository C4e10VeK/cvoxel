#include <stdio.h>
#include "utils/vec3s.h"
#include "window.h"

//TODO: рефакторнуть это
#include "graphics/vertexarray.h"
#include "graphics/buffer.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "camera.h"

#include <cglm/cglm.h>

VertexArray vao;
Buffer      vbo, ebo;
Shader      shader;
Texture     tex;

mat4s model, view, proj;
vec3s pos   = (vec3s){{0.0f, 0.0f, 5.0f}};
vec3s front = (vec3s){{0.0f, 0.0f, -1.0f}};
vec3s up    = (vec3s){{0.0f, 1.0f, 0.0f}};

Camera cam;

float yaw = -90.0f, pitch = 0.0f;

static void load()
{
    float vert[] = {
        1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    };

    GLuint ind[] = {
        0, 1, 2,
        3, 2, 1
    };

    vao = createVertexArray();
    vbo = createBuffer(GL_ARRAY_BUFFER);
    ebo = createBuffer(GL_ELEMENT_ARRAY_BUFFER);

    setBufferData(vbo, sizeof(vert), vert, GL_STATIC_DRAW);
    setBufferData(ebo, sizeof(ind), ind, GL_STATIC_DRAW);

    bindVertexArray(vao);
    bindBuffer(vbo);
    bindBuffer(ebo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), ((void*)0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    unbindBuffer(ebo);
    unbindBuffer(vbo);
    unbindVertexArray();

    shader = createShader("tvert.glsl", "tfrag.glsl");
    tex = createTexture("Brick.png", GL_TEXTURE_2D);

    cam = createCamera((vec3s){{0.0f, 0.0f, 5.0f}}, (mainWindow.size.x / mainWindow.size.y), 45.0f);

    glm_mat4_identity(model.raw);
    glm_perspective(cam.fov, cam.aspect, 0.1f, 100.0f, cam.proj.raw);

    glm_lookat(cam.pos.raw, vec3_add(cam.pos, cam.front).raw, cam.up.raw, cam.view.raw);
}

static void update()
{
    if (mainWindow.keyboardBtn[GLFW_KEY_ESCAPE].pressed) 
        glfwSetWindowShouldClose(mainWindow._glfwWindow, GLFW_TRUE);

    glm_perspective(cam.fov, cam.aspect, 0.1f, 100.0f, cam.proj.raw);

    glm_lookat(cam.pos.raw, vec3_add(cam.pos, cam.front).raw, cam.up.raw, cam.view.raw);
}

static void render()
{
    glClearColor(0.1f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    bindTexture(&tex, 0);

    bindShader(shader);
    shaderSetMat4(shader, "model", model.raw);
    shaderSetMat4(shader, "view", cam.view.raw);
    shaderSetMat4(shader, "proj", cam.proj.raw);

    bindVertexArray(vao);
    bindBuffer(ebo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    unbindBuffer(ebo);
    unbindVertexArray();
}

static void destroy()
{
    deleteShader(&shader);
    deleteBuffer(&vbo);
    deleteVertexArray(&vao);
}

static void crrs()
{
    cam.yaw   += mainWindow.mouse.delta.x * 0.1f;
    cam.pitch += mainWindow.mouse.delta.y * 0.1f;

    cam.pitch = glm_clamp(cam.pitch, -89.0f, 89.0f);

    cam.front = (vec3s){{
        cosf(glm_rad(cam.yaw)) * cosf(glm_rad(cam.pitch)),
        sinf(glm_rad(cam.pitch)),
        sinf(glm_rad(cam.yaw)) * cosf(glm_rad(cam.pitch))
    }};

    glm_vec3_normalize(cam.front.raw);
}

int main()
{
    createWindow(800, 600, "cwindow", load, update, render, destroy);
    mainWindow.cursorUpdate = crrs;
    runWindow();
    
    return 0;
}
