#include "texture.h"
#include <assert.h>
#include <stdlib.h>
#include <stb_image.h>

static void _createTexture2D(Texture* tex, const char* path)
{
    int nr, x, y;
    unsigned char* imgData = NULL;
    imgData = stbi_load(path, &x, &y, &nr, 0);

    tex->size = (vec2s){{x, y}};

    glTextureStorage2D(tex->texHandel, 1, GL_RGBA8, x, y);
    glTextureSubImage2D(tex->texHandel, 0, 0, 0, x, y, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    
    glTextureParameteri(tex->texHandel, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex->texHandel, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTextureParameteri(tex->texHandel, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex->texHandel, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(imgData);
}

Texture createTexture(const char *texPath, GLenum texType)
{
    Texture tex = {
        .texType = texType
    };
          
    glCreateTextures(texType, 1, &tex.texHandel);

    switch (texType)
    {
        case GL_TEXTURE_2D:
            _createTexture2D(&tex, texPath);
            break;
        case GL_TEXTURE_2D_ARRAY:
            fprintf(stderr, "Texture array doesn't work");
            exit(1);
            break;
        default:
            break;
    } 

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
