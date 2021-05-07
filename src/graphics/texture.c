#include "texture.h"
#include "cglm/types-struct.h"
#include <assert.h>
#include <stdlib.h>
#include <stb_image.h>

Texture createTexture(const char *texPath, GLenum texType)
{
    Texture tex;
    int nr, x, y;
    unsigned char* imgData = NULL;

    char* realPath = realpath(texPath, NULL);
    assert(realPath);

    imgData = stbi_load(realPath, &x, &y, &nr, 0);
    assert(imgData);

    tex.size = (vec2s){{x, y}};

    glCreateTextures(texType, 1, &tex.texHandel);

    glTextureStorage2D(tex.texHandel, 1, GL_RGBA8, x, y);
    glTextureSubImage2D(tex.texHandel, 0, 0, 0, x, y, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    glTextureParameteri(tex.texHandel, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex.texHandel, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(tex.texHandel, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex.texHandel, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(imgData);

    return tex;
}

void bindTexture(Texture tex, int texUnit)
{
    glBindTextureUnit(texUnit, tex.texHandel);
}

void deleteTexture(Texture *tex)
{
    glDeleteTextures(1, &tex->texHandel);
    tex->size = (vec2s){{0, 0}};
    tex->texType = 0;
}
