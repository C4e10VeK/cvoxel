#include "vertexarray.h"

VertexArray createVertexArray()
{
    VertexArray va;
    glCreateVertexArrays(1, &va);
    return va;
}

void bindVertexArray(VertexArray vertexArray)
{
    glBindVertexArray(vertexArray);
}

void unbindVertexArray()
{
    glBindVertexArray(0);
}

void deleteVertexArray(VertexArray* vertexArray)
{
    glDeleteVertexArrays(1, vertexArray);
}
