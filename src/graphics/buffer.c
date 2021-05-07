#include "buffer.h" 

Buffer createBuffer(GLenum target)
{
    Buffer buf = {
        .target = target
    };

    glCreateBuffers(1, &buf.bufHandel);

    return buf;
}

void bindBuffer(Buffer buffer)
{
    glBindBuffer(buffer.target, buffer.bufHandel);
}

void unbindBuffer(Buffer buffer)
{
    glBindBuffer(buffer.target, 0);
}

void setBufferData(Buffer buffer, size_t size, void *data, GLenum drawType)
{
    glNamedBufferData(buffer.bufHandel, size, data, drawType);
}

void deleteBuffer(Buffer *buffer)
{
    glDeleteBuffers(1, &buffer->bufHandel);
    buffer->target = 0;
}
