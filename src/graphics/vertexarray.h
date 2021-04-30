#ifndef CVOXEL_VERTEXARRAY_H
#define CVOXEL_VERTEXARRAY_H

#include <glad/gl.h>

typedef GLuint VertexArray;

VertexArray createVertexArray();

void bindVertexArray(VertexArray vertexArray);

void unbindVertexArray();

void deleteVertexArray(VertexArray* vertexArray);

#endif
