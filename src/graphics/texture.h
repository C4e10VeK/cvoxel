#ifndef CVOXEL_TEXTURE_H
#define CVOXEL_TEXTURE_H

#include <glad/gl.h>
#include <cglm/types-struct.h>

typedef struct
{
    GLuint texHandel;
    vec2s size;
    GLenum texType;
} Texture;

Texture createTexture(const char* texPath, GLenum texType);

void bindTexture(Texture* tex, int texUnit);

void deleteTexture(Texture* tex);

#endif
