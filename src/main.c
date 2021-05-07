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

mat4s model;

Camera cam;

bool curDis = true;

static void load()
{
    int a, b;

    float vert[] = {
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    };

    GLuint ind[] = {
        0, 1, 2,
        3, 2, 1,

        4, 5, 6,
        7, 6, 5,

        8, 9, 10,
        11, 10, 9,

        12, 13, 14,
        15, 14, 13,

        16, 17, 18,
        19, 18, 17,

        20, 21, 22,
        23, 22, 21
    };

    shader = createShader("/home/chelovek/stream/cvoxel/build/tvert.glsl", 
			"/home/chelovek/stream/cvoxel/build/tfrag.glsl");

    vao = createVertexArray();
    vbo = createBuffer(GL_ARRAY_BUFFER);
    ebo = createBuffer(GL_ELEMENT_ARRAY_BUFFER);

    setBufferData(vbo, sizeof(vert), vert, GL_STATIC_DRAW);
    setBufferData(ebo, sizeof(ind), ind, GL_STATIC_DRAW);

    bindVertexArray(vao);
    bindBuffer(vbo);
    bindBuffer(ebo);

    a = glGetAttribLocation(shader.shaderHndel, "aPos");
    b = glGetAttribLocation(shader.shaderHndel, "aTexCoord");

    glEnableVertexAttribArray(a);
    glEnableVertexAttribArray(b);

    glVertexAttribPointer(a, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), ((void*)0));
    glVertexAttribPointer(b, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    unbindBuffer(ebo);
    unbindBuffer(vbo);
    unbindVertexArray();

    tex = createTexture("/home/chelovek/stream/cvoxel/build/Brick.png", GL_TEXTURE_2D);

    cam = createCamera((vec3s){{0.0f, 0.0f, 5.0f}}, 45.0f);

    glm_mat4_identity(model.raw);
    glm_perspective(cam.fov, cam.aspect, 0.1f, 100.0f, cam.proj.raw);

    glm_lookat(cam.pos.raw, vec3_add(cam.pos, cam.front).raw, cam.up.raw, cam.view.raw);
}

//TODO: рефакторнуть кастыль
static void update()
{
    float speed = 2.5f;

    if (mainWindow.keyboardBtns[GLFW_KEY_ESCAPE].pressed) 
        glfwSetWindowShouldClose(mainWindow._glfwWindow, GLFW_TRUE);

    if (mainWindow.keyboardBtns[GLFW_KEY_W].pressed) 
    {
        glm_vec3_muladds(cam.front.raw, (speed * mainWindow.deltaTime), cam.pos.raw);
    }

    if (mainWindow.keyboardBtns[GLFW_KEY_S].pressed) 
    {
        glm_vec3_muladds(cam.front.raw, -(speed * mainWindow.deltaTime), cam.pos.raw);
    }

    if (mainWindow.keyboardBtns[GLFW_KEY_A].pressed) 
    {
        glm_vec3_muladds(cam.right.raw, -(speed * mainWindow.deltaTime), cam.pos.raw);
    }

    if (mainWindow.keyboardBtns[GLFW_KEY_D].pressed) 
    {
        glm_vec3_muladds(cam.right.raw, (speed * mainWindow.deltaTime), cam.pos.raw);
    }

    //shader reload
    if (mainWindow.keyboardBtns[GLFW_KEY_R].pressed)
    {
        deleteShader(&shader);
        shader = createShader("tvert.glsl", "tfrag.glsl");
    }

    cam.aspect = (mainWindow.size.x / mainWindow.size.y);
    glm_perspective(cam.fov, cam.aspect, 0.1f, 100.0f, cam.proj.raw);
    glm_lookat(cam.pos.raw, vec3_add(cam.pos, cam.front).raw, cam.up.raw, cam.view.raw);
}

static void render()
{
    glClearColor(0.1f, 0.5f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bindTexture(tex, 0);

    bindShader(shader);
    shaderSetMat4(shader, "model", model.raw);
    shaderSetMat4(shader, "view", cam.view.raw);
    shaderSetMat4(shader, "proj", cam.proj.raw);

    bindVertexArray(vao);
    bindBuffer(ebo);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
    unbindBuffer(ebo);
    unbindVertexArray();
}

static void destroy()
{
    deleteTexture(&tex);
    deleteShader(&shader);
    deleteBuffer(&vbo);
    deleteVertexArray(&vao);
}

static void cursorUpd()
{
    cameraVectorUpdate(&cam);
}

int main()
{
    createWindow(800, 600, "cwindow", load, update, render, destroy);
    mainWindow.cursorUpdate = cursorUpd;
    runWindow();
    
    return 0;
}
