#ifndef CVOXEL_TEXTURE_H
#define CVOXEL_TEXTURE_H

#include <glad/gl.h>
#include "../../utils/types.h"

typedef struct
{
	GLuint handle;
	GLenum target;

	struct
	{
		i32 width;
		i32 height;
	} size;

} Texture;

Texture textureForFramebufferCreate(i32 width, i32 height);

Texture textureLoadFromFile(const char *path, GLenum type);

void textureBind(const Texture *texture, i32 texUnit);

void textureDelete(Texture *texture);

#endif // CVOXEL_TEXTURE_H
