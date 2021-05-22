#include "chunk.h"
#include "../utils/vec3s.h"
#include "../graphics/renderer.h"
#include <stddef.h>

const float vert[] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

const float uv[] = {
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

const unsigned int indices[] = {
    0, 1, 2,
    3, 2, 1
};

Chunk genFlatChunk(vec3s position)
{
    Chunk tmpChunk;

    tmpChunk._pos = position;
    tmpChunk._offset = (vec3s){{CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}};

    for (size_t x = 0; x < CHUNK_SIZE; x++)
        for (size_t y = 0; y < CHUNK_SIZE; y++)
            for (size_t z = 0; z < CHUNK_SIZE; z++)
            {
                Voxel id = 1;

                if (y >= 5) id = 0;

                tmpChunk.voxels[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z] = id;
            }

    return tmpChunk;
}

static void _initChunkMesh(ChunkMesh* chunkMesh)
{
    chunkMesh->mesh._vao = createVertexArray();
    chunkMesh->mesh._vbo = createBuffer(GL_ARRAY_BUFFER);
    chunkMesh->mesh._ebo = createBuffer(GL_ELEMENT_ARRAY_BUFFER);
    
    chunkMesh->mesh._indCount = chunkMesh->mesh._indeces._size;

    setBufferData(chunkMesh->mesh._vbo, 
            chunkMesh->mesh._vertixes._size * chunkMesh->mesh._vertixes._typesize, 
            chunkMesh->mesh._vertixes._items, 
            GL_STATIC_DRAW);

    setBufferData(chunkMesh->mesh._ebo, 
            chunkMesh->mesh._indeces._size * chunkMesh->mesh._indeces._typesize, 
            chunkMesh->mesh._indeces._items, 
            GL_STATIC_DRAW);

    bindVertexArray(chunkMesh->mesh._vao);
    bindBuffer(chunkMesh->mesh._vbo);
    bindBuffer(chunkMesh->mesh._ebo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));

    unbindBuffer(chunkMesh->mesh._vbo);
    unbindBuffer(chunkMesh->mesh._ebo);
    unbindVertexArray();
}

ChunkMesh* genChunkMesh(Chunk* chunk)
{
    unsigned int i = 0;
    vec3s chunkPos = vec3_multiply(chunk->_pos, chunk->_offset);
    ChunkMesh* chunkMesh = calloc(1, sizeof(ChunkMesh));
    VECTOR_INIT(chunkMesh->mesh._vertixes, float);
    VECTOR_INIT(chunkMesh->mesh._indeces, unsigned int);

    for (int x = 0; x < CHUNK_SIZE; x++)
        for (int y = 0; y < CHUNK_SIZE; y++)
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                Voxel voxId = chunk->voxels[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z];

                if (voxId != 0)
                {
                    float a[] = {
                        vert[0] + chunkPos.x + x, vert[1]  + chunkPos.y + y, vert[2]  + chunkPos.z + z,  1.0f, 0.0f,
                        vert[3] + chunkPos.x + x, vert[4]  + chunkPos.y + y, vert[5]  + chunkPos.z + z,  1.0f, 1.0f,
                        vert[6] + chunkPos.x + x, vert[7]  + chunkPos.y + y, vert[8]  + chunkPos.z + z,  0.0f, 0.0f,
                        vert[9] + chunkPos.x + x, vert[10] + chunkPos.y + y, vert[11] + chunkPos.z + z,  0.0f, 1.0f
                    };

                    unsigned int b[] = {
                        0 + i, 1 + i, 2 + i,
                        3 + i, 2 + i, 1 + i
                    };

                    VECTOR_ADD_RANGE(chunkMesh->mesh._vertixes, a);
                    VECTOR_ADD_RANGE(chunkMesh->mesh._indeces, b);
                    i += 4;
                }
            }

    _initChunkMesh(chunkMesh);
    return chunkMesh;
}

void drawChunk(ChunkMesh* chunkMesh)
{    
    drawMesh(&chunkMesh->mesh);
}

void destroyChunkMesh(ChunkMesh* chunkMesh)
{
    VECTOR_FREE(chunkMesh->mesh._vertixes);
    VECTOR_FREE(chunkMesh->mesh._indeces);

    deleteBuffer(&chunkMesh->mesh._ebo);
    deleteBuffer(&chunkMesh->mesh._vbo);
    deleteVertexArray(&chunkMesh->mesh._vao);

    free(chunkMesh);
}
