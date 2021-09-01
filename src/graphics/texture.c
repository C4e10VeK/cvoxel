#include "texture.h"
#include <assert.h>
#include <stdlib.h>
#include <stb_image.h>

Texture createCustomTexture()
{
    Texture tex;
    int x = 2, y = 2;
    unsigned char imgData[] = {
        0, 150, 0, 255, 150, 150, 150, 255,
        0, 0, 0, 255,   0, 0, 0, 255
    };

    glCreateTextures(GL_TEXTURE_2D, 1, &tex.texHandel);

    tex.size = (vec2s){{x, y}};

    glTextureStorage2D(tex.texHandel, 1, GL_RGBA8, x, y);
    glTextureSubImage2D(tex.texHandel, 0, 0, 0, x, y, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    glTextureParameteri(tex.texHandel, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex.texHandel, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTextureParameteri(tex.texHandel, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex.texHandel, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return tex;
}

Texture createTexture(const char *texPath, GLenum texType)
{
    Texture tex = {
        .texType = texType
    };
          
    glCreateTextures(texType, 1, &tex.texHandel);

	int nr, x, y;
    unsigned char* imgData = NULL;
    imgData = stbi_load(texPath, &x, &y, &nr, 0);

    tex.size = (vec2s){{x, y}};

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
