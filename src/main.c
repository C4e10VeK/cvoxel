#include <stdio.h>
#include <memory.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include "window.h"

//TODO: refactor this
#include "gl/shader.h"
#include "gl/texture.h"
#include "camera.h"
#include "world/chunk.h"

#define VERT_PATH "../res/shaders/vert.glsl"
#define FRAG_PATH "../res/shaders/frag.glsl"
#define TEXTURE_PATH "../res/textures/brick.png"

#define WORLD_VOL 4096

//Speed test
#include <time.h>
#include "utils/macro.h"

#define clear() printf("\033[H\033[J")

Shader      shader;
Texture     tex;
Chunk       chunks[WORLD_VOL];
ChunkMesh   meshes[WORLD_VOL];
Camera      cam;
mat4s       model;

static void load()
{
    shader = shaderInit(VERT_PATH, FRAG_PATH, 3, (ShaderAttrib[]){
														{0, "aPos"}, 
														{1, "aTexCoord"}, 
														{2, "aLight"}
													});

    tex = textureLoadFromFile(TEXTURE_PATH, GL_TEXTURE_2D);

    for (size_t x = 0; x < 16; x++)
    {
        for (size_t y = 0; y < 16; y++)
        {
            for (size_t z = 0; z < 16; z++) 
            {
                Chunk* pChunk = &chunks[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z];
                *pChunk = chunkInit((vec3s){{x, y, z}});
                memset(pChunk->adjacentChunks.raw, 0, 6 * sizeof(Chunk*));

                pChunk->adjacentChunks._back = (int)z - 1 >= 0 ? &chunks[(y * CHUNK_SIZE + x) * CHUNK_SIZE + (z - 1)] : NULL;

                pChunk->adjacentChunks._front = (int)z + 1 < 16 ? &chunks[(y * CHUNK_SIZE + x) * CHUNK_SIZE + (z + 1)] : NULL;
                
                pChunk->adjacentChunks._left = (int)x - 1 >= 0 ? &chunks[(y * CHUNK_SIZE + (x - 1)) * CHUNK_SIZE + z] : NULL;

                pChunk->adjacentChunks._right = (int)x + 1 < 16 ? &chunks[(y * CHUNK_SIZE + (x + 1)) * CHUNK_SIZE + z] : NULL;
                
                pChunk->adjacentChunks._bottom = (int)y - 1 >= 0 ? &chunks[((y - 1) * CHUNK_SIZE + x) * CHUNK_SIZE + z] : NULL;
                
                pChunk->adjacentChunks._top = (int)y + 1 < 16 ? &chunks[((y + 1) * CHUNK_SIZE + x) * CHUNK_SIZE + z] : NULL;
            }
        }
    }

    for (size_t i = 0; i < WORLD_VOL; i++)
    {
        meshes[i] = genChunkMesh(&chunks[i]);
        chunks[i]._chunkMesh = &meshes[i]; 
    } 

    cam = createCamera((vec3s){{16.0f, 32.0f, 16.0f}}, 45.0f, 0.15);

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
        shaderDelete(shader);
        shader = shaderInit(VERT_PATH, FRAG_PATH, 0, NULL);
    }
    //----------------------------------------------------------------

    cam.aspect = (mainWindow.size.x / mainWindow.size.y);
    cam.proj = glms_perspective(cam.fov, cam.aspect, 0.1f, 1000.0f);
    cam.view = glms_lookat(cam.pos, glms_vec3_add(cam.pos, cam.front), cam.up);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

static void render()
{
    glClearColor(0.1f, 0.5f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    textureBind(&tex, 0);

    shaderBind(shader);
    shaderSetMatrix4(shader, "model", model);
    shaderSetMatrix4(shader, "view", cam.view);
    shaderSetMatrix4(shader, "proj", cam.proj);

    for (size_t i = 0; i < WORLD_VOL; i++)
    {
        drawChunkMesh(&meshes[i]);
    }
}

static void destroy()
{
    textureDelete(&tex);
    shaderDelete(shader);

    for (size_t i = 0; i < WORLD_VOL; i++)
        destroyChunkMesh(&meshes[i]);
}

static void cursorUpd()
{
    cameraVectorUpdate(&cam);
}

int main()
{
  mat4s foo = glms_mat4_identity();
  foo = glms_translate(foo, (vec3s){{0.5f, 5.0f, 2.0f}});
    createWindow(800, 600, "cwindow", load, update, render, destroy, cursorUpd);
    runWindow();
    
    return 0;
}

