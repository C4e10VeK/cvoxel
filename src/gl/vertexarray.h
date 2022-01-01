#ifndef RAYCASTING_VERTEXARRAY_H
#define RAYCASTING_VERTEXARRAY_H

#include <glad/gl.h>

typedef GLuint VertexArray;

VertexArray vertexArrayCreate();

void vertexArrayBind(VertexArray vertexArray);

void vertexArrayUnbind();

void vertexArrayDelete(VertexArray vertexArray);

#endif // RAYCASTING_VERTEXARRAY_H
