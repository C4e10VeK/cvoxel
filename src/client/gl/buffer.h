#ifndef CVOXEL_BUFFER_H
#define CVOXEL_BUFFER_H

#include <stddef.h>
#include "glad/gl.h"

typedef struct
{
	GLuint handle;
	GLenum target;
} Buffer;

typedef Buffer FrameBuffer;
typedef Buffer RenderBuffer;

Buffer bufferCreate(GLenum target);

FrameBuffer frameBufferCreate();

RenderBuffer renderBufferCreate();

void bufferBind(const Buffer *buffer);

void frameBufferBind(const FrameBuffer *buffer);

void renderBufferBind(const RenderBuffer *buffer);

void bufferUnbind(const Buffer *buffer);

void frameBufferUnbind(const FrameBuffer *buffer);

void renderBufferUnbind(const RenderBuffer *buffer);

void bufferSetData(Buffer *buffer, size_t size, void *data, GLenum drawType);

void bufferSetSubData(Buffer *buffer, GLintptr offset, size_t size, void *data);

void bufferDelete(Buffer *buffer);

void frameBufferDelete(FrameBuffer *buffer);

void renderBufferDelete(RenderBuffer *buffer);

#endif // CVOXEL_BUFFER_H
