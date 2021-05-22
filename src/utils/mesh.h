#ifndef CVOXEL_MESH_H
#define CVOXEL_MESH_H

#include <cvector.h>
#include "../graphics/vertexarray.h"
#include "../graphics/buffer.h"

typedef struct
{
    unsigned int _indCount;
    VertexArray _vao;
    Buffer _vbo, _ebo;

    Vector _vertixes;
    Vector _indeces; 
} Mesh;

#endif

