#ifndef CVOXEL_CHUNK_H
#define CVOXEL_CHUNK_H

#include <stdint.h>
#include <cglm/types-struct.h>
#include "../graphics/vertexarray.h"
#include "../graphics/buffer.h"
#include "../utils/mesh.h"

#define CHUNK_SIZE 16
#define CHUNK_VOL  4096

typedef uint32_t Voxel;

typedef struct
{
    Mesh mesh;
} ChunkMesh;

typedef struct Chunk
{
    Voxel voxels[CHUNK_VOL];
    vec3s _pos, _offset;

    union
    {
        struct Chunk* raw[6];

        struct
        {
            struct Chunk* _front;
            struct Chunk* _back;
            struct Chunk* _top;
            struct Chunk* _bottom;
            struct Chunk* _left;
            struct Chunk* _right;
        };
    } adjacentChunks;

    ChunkMesh* _chunkMesh;
} Chunk;

Chunk chunkInit(vec3s position);

ChunkMesh* genChunkMesh(const Chunk* chuhk);
void drawChunkMesh(ChunkMesh* chunkMesh);
void destroyChunkMesh(ChunkMesh* chunkMesh);

#endif

