#include "texture.h"
#include <stdlib.h>
#include <stb_image.h>

Texture textureForFramebufferCreate(i32 width, i32 height)
{
	Texture res = {
		.target = GL_TEXTURE_2D,
		.size = { .width = width, .height = height }
	};

	glCreateTextures(GL_TEXTURE_2D, 1, &res.handle);
	glTextureStorage2D(res.handle, 1, GL_RGBA8UI, width, height);
	
	glTextureParameteri(res.handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(res.handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return res;
}

Texture textureLoadFromFile(const char *path, GLenum type)
{
	int nr, w, h;
	unsigned char *data = NULL;
	Texture res = {
		.target = type
	};

	if (!path)
		abort();

	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(path, &w, &h, &nr, 0);

	res.size.width = w;
	res.size.height = h;

	glCreateTextures(type, 1, &res.handle);
	glTextureStorage2D(res.handle, 1, GL_RGBA8, w, h);
	glTextureSubImage2D(res.handle, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTextureParameteri(res.handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(res.handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(res.handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(res.handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(data);

	return res;
}

void textureBind(const Texture *texture, i32 texUnit)
{
	glBindTextureUnit(texUnit, texture->handle);
}

void textureDelete(Texture *texture)
{
	glDeleteTextures(1, &texture->handle);
	texture->handle = 0;
	texture->target = 0;
	texture->size.width = texture->size.height = 0;
}

