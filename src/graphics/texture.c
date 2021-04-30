#include "texture.h"
#include "cglm/types-struct.h"
#include <assert.h>
#include <stb_image.h>

Texture createTexture(const char *texPath, GLenum texType)
{
    Texture tex;
    unsigned char* imgData;
    int nr, x, y;

    imgData = stbi_load(texPath, &x, &y, &nr, 0);
    assert(imgData);

    tex.size = (vec2s){{x, y}};

    glCreateTextures(texType, 1, &tex.texHandel);

    glTextureStorage2D(tex.texHandel, 1, GL_RGBA8, x, y);
    glTextureSubImage2D(tex.texHandel, 0, 0, 0, x, y, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    stbi_image_free(imgData);

    return tex;
}

void bindTexture(Texture *tex, int texUnit)
{
    glBindTextureUnit(texUnit, tex->texHandel);
}

void deleteTexture(Texture *tex)
{
    glDeleteTextures(1, &tex->texHandel);
    tex->size = (vec2s){{0, 0}};
    tex->texType = 0;
}
