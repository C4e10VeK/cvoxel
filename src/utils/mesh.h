#ifndef CVOXEL_MESH_H
#define CVOXEL_MESH_H

#include <cvector.h>
#include <stdint.h>
#include "../gl/vertexarray.h"
#include "../gl/buffer.h"

typedef Vector(float) VectorFloat;
typedef Vector(uint32_t) VectorU32;

typedef struct
{
    uint32_t _vertCount;
    uint32_t _indCount;
    VertexArray _vao;
    Buffer _vbo, _ebo;

    VectorFloat _vertices;
    VectorU32 _indeces; 
} Mesh;

#endif

