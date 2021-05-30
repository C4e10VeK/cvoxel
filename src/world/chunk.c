#include "chunk.h"
#include "../utils/vec3s.h"
#include "../graphics/renderer.h"

const float VERTICES[] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

const float UV[] = {
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

const uint32_t INDICES[] = {
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
    chunkMesh->mesh._vao      = createVertexArray();
    chunkMesh->mesh._vbo      = createBuffer(GL_ARRAY_BUFFER);
    chunkMesh->mesh._ebo      = createBuffer(GL_ELEMENT_ARRAY_BUFFER);
    chunkMesh->mesh._indCount = chunkMesh->mesh._indeces._size;

    setBufferData(chunkMesh->mesh._vbo, 
            chunkMesh->mesh._vertices._size * chunkMesh->mesh._vertices._typesize, 
            chunkMesh->mesh._vertices._items, 
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

static void _addFrontFace(vec3s offset, ChunkMesh* chunkMesh)
{
        float a[] = {
        1.0f + offset.x, 0.0f  + offset.y, 0.0f + offset.z,  1.0f, 0.0f,
        1.0f + offset.x, 1.0f  + offset.y, 0.0f + offset.z,  1.0f, 1.0f,
        0.0f + offset.x, 0.0f  + offset.y, 0.0f + offset.z,  0.0f, 0.0f,
        0.0f + offset.x, 1.0f  + offset.y, 0.0f + offset.z,  0.0f, 1.0f
    };

    for (size_t i = 0; i < 6; i++)
    {
        uint32_t iValue = INDICES[i] + chunkMesh->mesh._vertCount;
        cVectorAddItem(&chunkMesh->mesh._indeces, &iValue);
    }

    VECTOR_ADD_RANGE(chunkMesh->mesh._vertices, a);
    chunkMesh->mesh._vertCount += 4;
}

static void _addBackFace(vec3s offset, ChunkMesh* chunkMesh)
{
        float a[] = {
        1.0f + offset.x, 0.0f  + offset.y, 1.0f + offset.z,  1.0f, 0.0f,
        1.0f + offset.x, 1.0f  + offset.y, 1.0f + offset.z,  1.0f, 1.0f,
        0.0f + offset.x, 0.0f  + offset.y, 1.0f + offset.z,  0.0f, 0.0f,
        0.0f + offset.x, 1.0f  + offset.y, 1.0f + offset.z,  0.0f, 1.0f
    };

    for (size_t i = 0; i < 6; i++)
    {
        uint32_t iValue = INDICES[i] + chunkMesh->mesh._vertCount;
        cVectorAddItem(&chunkMesh->mesh._indeces, &iValue);
    }

    VECTOR_ADD_RANGE(chunkMesh->mesh._vertices, a);
    chunkMesh->mesh._vertCount += 4;
}


static void _addBottomFace(vec3s offset, ChunkMesh* chunkMesh)
{
    float a[] = {
        1.0f + offset.x, 0.0f  + offset.y, 0.0f + offset.z,  1.0f, 0.0f,
        1.0f + offset.x, 0.0f  + offset.y, 1.0f + offset.z,  1.0f, 1.0f,
        0.0f + offset.x, 0.0f  + offset.y, 0.0f + offset.z,  0.0f, 0.0f,
        0.0f + offset.x, 0.0f  + offset.y, 1.0f + offset.z,  0.0f, 1.0f
    };

    for (size_t i = 0; i < 6; i++)
    {
        uint32_t iValue = INDICES[i] + chunkMesh->mesh._vertCount;
        cVectorAddItem(&chunkMesh->mesh._indeces, &iValue);
    }

    VECTOR_ADD_RANGE(chunkMesh->mesh._vertices, a);
    chunkMesh->mesh._vertCount += 4;
}

static void _addTopFace(vec3s offset, ChunkMesh* chunkMesh)
{
    float a[] = {
        1.0f + offset.x, 1.0f  + offset.y, 0.0f + offset.z,  1.0f, 0.0f,
        1.0f + offset.x, 1.0f  + offset.y, 1.0f + offset.z,  1.0f, 1.0f,
        0.0f + offset.x, 1.0f  + offset.y, 0.0f + offset.z,  0.0f, 0.0f,
        0.0f + offset.x, 1.0f  + offset.y, 1.0f + offset.z,  0.0f, 1.0f
    };

    for (size_t i = 0; i < 6; i++)
    {
        uint32_t iValue = INDICES[i] + chunkMesh->mesh._vertCount;
        cVectorAddItem(&chunkMesh->mesh._indeces, &iValue);
    }

    VECTOR_ADD_RANGE(chunkMesh->mesh._vertices, a);
    chunkMesh->mesh._vertCount += 4;
}

ChunkMesh* genChunkMesh(const Chunk* chunk)
{ 
    vec3s chunkPos = vec3_multiply(chunk->_pos, chunk->_offset);
    ChunkMesh* chunkMesh = calloc(1, sizeof(ChunkMesh));
    VECTOR_INIT(chunkMesh->mesh._vertices, float);
    VECTOR_INIT(chunkMesh->mesh._indeces, uint32_t);

    for (int x = 0; x < CHUNK_SIZE; x++)
        for (int y = 0; y < CHUNK_SIZE; y++)
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                Voxel voxId = chunk->voxels[(y * CHUNK_SIZE + x) * CHUNK_SIZE + z];

                if (voxId == 0) continue;
                
                _addBackFace(vec3_add(chunkPos, (vec3s){{x, y, z}}), chunkMesh);
                _addFrontFace(vec3_add(chunkPos, (vec3s){{x, y, z}}), chunkMesh);
                _addBottomFace(vec3_add(chunkPos, (vec3s){{x, y, z}}), chunkMesh);
                _addTopFace(vec3_add(chunkPos, (vec3s){{x, y, z}}), chunkMesh);
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
    VECTOR_FREE(chunkMesh->mesh._vertices);
    VECTOR_FREE(chunkMesh->mesh._indeces);

    deleteBuffer(&chunkMesh->mesh._ebo);
    deleteBuffer(&chunkMesh->mesh._vbo);
    deleteVertexArray(&chunkMesh->mesh._vao);

    free(chunkMesh);
}
