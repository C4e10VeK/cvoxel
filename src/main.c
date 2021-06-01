#include <stdio.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include "window.h"

//TODO: refactor this
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "camera.h"
#include "world/chunk.h"

#define VERT_PATH "/home/chelovek/stream/cvoxel/build/tvert.glsl"
#define FRAG_PATH "/home/chelovek/stream/cvoxel/build/tfrag.glsl"
#define TEXTURE_PATH "/home/chelovek/stream/cvoxel/build/Brick.png"

#define WORLD_VOL 512

#define clear() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))

Shader      shader;
Texture     tex;
Chunk       chunks[WORLD_VOL];
ChunkMesh*  meshes[WORLD_VOL];
Camera      cam;
mat4s       model;

static void _drawConsoleBox()
{
    clear();
    puts(
        "╭───────────────────────────────────────╮\n"
        "|                                       |\n"
        "╰───────────────────────────────────────╯\n"
    );
}

static void load()
{
    shader = createShader(VERT_PATH, FRAG_PATH);

    tex = createTexture(TEXTURE_PATH, GL_TEXTURE_2D); 

    for (size_t x = 0; x < 16; x++)
    {
        for (size_t y = 0; y < 2; y++)
        {
            for (size_t z = 0; z < 16; z++) 
            {
                Chunk* pChunk = &chunks[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z];
                *pChunk = chunkInit((vec3s){{x, y, z}});
                meshes[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z] = genChunkMesh(pChunk, chunks);
                pChunk->_chunkMesh = meshes[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z];
            }
        }
    }

    cam = createCamera((vec3s){{16.0f, 6.0f, 16.0f}}, 45.0f, 0.15);

    model = glms_mat4_identity();
    cam.proj = glms_perspective(cam.fov, cam.aspect, 0.1f, 1000.0f);
    cam.view = glms_lookat(cam.pos, glms_vec3_add(cam.pos, cam.front), cam.up);
}

static void update()
{
    float speed = 10.0f * mainWindow.deltaTime;

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
        glm_vec3_muladds(cam.front.raw, speed, cam.pos.raw);
    }

    if (mainWindow.keyboardBtns[GLFW_KEY_S].pressed) 
    {
        glm_vec3_muladds(cam.front.raw, -speed, cam.pos.raw);
    }

    if (mainWindow.keyboardBtns[GLFW_KEY_A].pressed) 
    {
        glm_vec3_muladds(cam.right.raw, -speed, cam.pos.raw);
    }

    if (mainWindow.keyboardBtns[GLFW_KEY_D].pressed) 
    {
        glm_vec3_muladds(cam.right.raw, speed, cam.pos.raw);
    }

    //shader reload
    //----------------------------------------------------------------
    if (mainWindow.keyboardBtns[GLFW_KEY_R].pressed)
    {
        deleteShader(&shader);
        shader = createShader(VERT_PATH, FRAG_PATH);
    }
    //----------------------------------------------------------------

    cam.aspect = (mainWindow.size.x / mainWindow.size.y);
    cam.proj = glms_perspective(cam.fov, cam.aspect, 0.1f, 1000.0f);
    cam.view = glms_lookat(cam.pos, glms_vec3_add(cam.pos, cam.front), cam.up);
    
    _drawConsoleBox();
    gotoxy(2, 2);
    printf("(x:%f y:%f z:%f)\n", cam.pos.x, cam.pos.y, cam.pos.z);

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
}

static void render()
{
    glClearColor(0.1f, 0.5f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bindTexture(tex, 0);

    bindShader(shader);
    shaderSetMat4(shader, "model", model.raw);
    shaderSetMat4(shader, "view", cam.view.raw);
    shaderSetMat4(shader, "proj", cam.proj.raw);

    for (size_t i = 0; i < WORLD_VOL; i++)
        drawChunk(meshes[i]);
}

static void destroy()
{
    deleteTexture(&tex);
    deleteShader(&shader);

    for (size_t i = 0; i < WORLD_VOL; i++)
        destroyChunkMesh(meshes[i]);
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

