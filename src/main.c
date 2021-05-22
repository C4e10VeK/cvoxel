#include <stdio.h>
#include <cglm/cglm.h>
#include "utils/vec3s.h"
#include "window.h"

//TODO: refactor this
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "camera.h"
#include "world/chunk.h"

#define WORLD_VOL 512

Shader      shader;
Texture     tex;
Chunk       chunks[WORLD_VOL];
Camera      cam;
mat4s       model;

static void load()
{
    shader = createShader(
            "/home/chelovek/stream/cvoxel/build/tvert.glsl", 
			"/home/chelovek/stream/cvoxel/build/tfrag.glsl"
            );

    tex = createTexture("/home/chelovek/stream/cvoxel/build/Brick.png", GL_TEXTURE_2D); 

    for (size_t x = 0; x < 16; x++)
    {
        for (size_t y = 0; y < 2; y++)
        {
            for (size_t z = 0; z < 16; z++) 
            {
                Chunk* pChunk = &chunks[(y * 16 + x) * 16 + z];
                *pChunk = genFlatChunk((vec3s){{x, y, z}});
                pChunk->_chunkMesh = genChunkMesh(pChunk);
            }
        }
    }

    cam = createCamera((vec3s){{5.0f, 10.0f, 5.0f}}, 45.0f);

    glm_mat4_identity(model.raw);
    glm_perspective(cam.fov, cam.aspect, 0.1f, 100.0f, cam.proj.raw);

    glm_lookat(cam.pos.raw, vec3_add(cam.pos, cam.front).raw, cam.up.raw, cam.view.raw);
}

//TODO: refactor this
static void update()
{
    float speed = 2.5f;

    if (mainWindow.keyboardBtns[GLFW_KEY_ESCAPE].pressed) 
        glfwSetWindowShouldClose(mainWindow._glfwWindow, GLFW_TRUE);
    
    //Input mode
    //----------------------------------------------------------------------------
    if (mainWindow.keyboardBtns[GLFW_KEY_N].pressed)
    {
       glfwSetInputMode(mainWindow._glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
    }
    
    if (mainWindow.keyboardBtns[GLFW_KEY_H].pressed)
    {
       glfwSetInputMode(mainWindow._glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    }
    //----------------------------------------------------------------------------
    
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
    //----------------------------------------------------------------
    if (mainWindow.keyboardBtns[GLFW_KEY_R].pressed)
    {
        deleteShader(&shader);
        shader = createShader("tvert.glsl", "tfrag.glsl");
    }
    //----------------------------------------------------------------

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

    for (size_t i = 0; i < WORLD_VOL; i++)
        drawChunk(chunks[i]._chunkMesh);
}

static void destroy()
{
    deleteTexture(&tex);
    deleteShader(&shader);

    for (size_t i = 0; i < WORLD_VOL; i++)
        destroyChunkMesh(chunks[i]._chunkMesh);
}

static void cursorUpd()
{
    cameraVectorUpdate(&cam);
}

int main()
{
    createWindow(800, 600, "cwindow", load, update, render, destroy, cursorUpd);
    runWindow();
    
    return 0;
}

