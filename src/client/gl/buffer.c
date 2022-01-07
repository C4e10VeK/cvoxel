#include "buffer.h"

Buffer bufferCreate(GLenum target)
{
	Buffer res = {
		.target = target
	};

	glCreateBuffers(1, &res.handle);

	return res;
}

FrameBuffer frameBufferCreate()
{
	FrameBuffer res = {
		.target = GL_FRAMEBUFFER
	};

	glGenFramebuffers(1, &res.handle);

	return res;
}

RenderBuffer renderBufferCreate()
{
	RenderBuffer res = {
		.target = GL_RENDERBUFFER
	};

	glGenRenderbuffers(1, &res.handle);

	return res;
}

void bufferBind(const Buffer *buffer)
{
	glBindBuffer(buffer->target, buffer->handle);
}

void frameBufferBind(const FrameBuffer *buffer)
{
	glBindFramebuffer(buffer->target, buffer->handle);
}

void renderBufferBind(const RenderBuffer *buffer)
{
	glBindRenderbuffer(buffer->target, buffer->handle);
}

void bufferUnbind(const Buffer *buffer)
{
	glBindBuffer(buffer->target, 0);
}

void frameBufferUnbind(const FrameBuffer *buffer)
{
	glBindFramebuffer(buffer->target, 0);
}

void renderBufferUnbind(const RenderBuffer *buffer)
{
	glBindRenderbuffer(buffer->target, 0);
}

void bufferSetData(Buffer *buffer, size_t size, void *data, GLenum drawType)
{
	glNamedBufferData(buffer->handle, size, data, drawType);
}

void bufferSetSubData(Buffer *buffer, GLintptr offset, size_t size, void *data)
{
	glNamedBufferSubData(buffer->handle, offset, size, data);
}

void bufferDelete(Buffer *buffer)
{
	glDeleteBuffers(1, &buffer->handle);
	buffer->handle = 0;
	buffer->target = 0;
}

void frameBufferDelete(FrameBuffer *buffer)
{
	glDeleteFramebuffers(1, &buffer->handle);
	buffer->handle = 0;
	buffer->target = 0;
}

void renderBufferDelete(RenderBuffer *buffer)
{
	glDeleteRenderbuffers(1, &buffer->handle);
	buffer->handle = 0;
	buffer->target = 0;
}
