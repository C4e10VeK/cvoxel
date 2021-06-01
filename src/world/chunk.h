#ifndef CVOXEL_CHUNK_H
#define CVOXEL_CHUNK_H

#include "../graphics/vertexarray.h"
#include "../graphics/buffer.h"
#include "../utils/mesh.h"
#include <cglm/types-struct.h>

#define CHUNK_SIZE 16
#define CHUNK_VOL  4096

typedef uint32_t Voxel;

typedef struct
{
    Mesh mesh;
} ChunkMesh;

typedef struct
{
    Voxel voxels[CHUNK_VOL];
    vec3s _pos;
    vec3s _offset;

    ChunkMesh* _chunkMesh;
} Chunk;

Chunk chunkInit(vec3s position);

ChunkMesh* genChunkMesh(const Chunk* chuhk, Chunk* chunks);
void drawChunk(ChunkMesh* chunkMesh);
void destroyChunkMesh(ChunkMesh* chunkMesh);

#endif

