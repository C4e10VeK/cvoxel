#ifndef CVOXEL_BUFFER_H
#define CVOXEL_BUFFER_H

#include <glad/gl.h>
#include <stdlib.h>

typedef struct
{
    GLuint bufHandel;
    GLenum target;
} Buffer;

Buffer createBuffer(GLenum target);

void bindBuffer(Buffer buffer);
void unbindBuffer(Buffer buffer);

void setBufferData(Buffer buffer, size_t size, void* data, GLenum drawType);

void deleteBuffer(Buffer* buffer);

#endif
