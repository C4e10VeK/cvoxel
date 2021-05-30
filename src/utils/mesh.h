#ifndef CVOXEL_MESH_H
#define CVOXEL_MESH_H

#include <cvector.h>
#include "../graphics/vertexarray.h"
#include "../graphics/buffer.h"

typedef struct
{
    uint32_t _vertCount;
    uint32_t _indCount;
    VertexArray _vao;
    Buffer _vbo, _ebo;

    Vector _vertices;
    Vector _indeces; 
} Mesh;

#endif

