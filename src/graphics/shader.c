#include "shader.h"
#include <assert.h>
#include <stdio.h>
#include <limits.h>

#include <stdlib.h>

static void _checkError(GLuint glHandle, GLenum status,
    void (*GLget)(GLuint, GLenum, GLint*), 
    void (*GLinfoLog)(GLuint, GLsizei, GLsizei*, GLchar*)
)
{
    char log[1024];
    int success;

    GLget(glHandle, status, &success);

    if (!success)
    {
        GLinfoLog(glHandle, 1024, NULL, log);
        printf("%s\n", log);
        exit(1);
    }
}

static GLuint _compile(const char* path, GLenum type)
{
    GLuint sh;
    int length;
    char* sCode = NULL;
    FILE* f = NULL;

	assert(path);
    
    f = fopen(path, "rb"); //FIXME: local path doesn't work
    assert(f);
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    assert(length > 0);
    fseek(f, 0, SEEK_SET);
    sCode = calloc(1, length);
    fread(sCode, 1, length, f);

    sh = glCreateShader(type);
    glShaderSource(sh, 1, (const char* const*)&sCode, &length);
    glCompileShader(sh);
    _checkError(sh, GL_COMPILE_STATUS, (void (*)(GLuint, GLenum, GLint *)) glGetShaderiv,
                (void (*)(GLuint, GLsizei, GLsizei *, GLchar *)) glGetShaderInfoLog);
    
    fclose(f);
    free(sCode);

    return sh;
}

Shader createShader(const char *vertPath, const char *fragPath)
{
    Shader shader;

    GLuint vertexShader = _compile(vertPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = _compile(fragPath, GL_FRAGMENT_SHADER);

    shader.shaderHndel = glCreateProgram();

    glAttachShader(shader.shaderHndel, vertexShader);
    glAttachShader(shader.shaderHndel, fragmentShader);

    glLinkProgram(shader.shaderHndel);
    _checkError(shader.shaderHndel, GL_LINK_STATUS, (void (*)(GLuint, GLenum, GLint *)) glGetProgramiv,
                (void (*)(GLuint, GLsizei, GLsizei *, GLchar *)) glGetProgramInfoLog);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

void bindShader(Shader shader)
{
    glUseProgram(shader.shaderHndel);
}

void unbindShader()
{
    glUseProgram(0);
}


void shaderSetFloat(Shader shader, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(shader.shaderHndel, name), value);
}

void shaderSetVec3(Shader shader, const char *name, vec3 vec)
{
    glUniform3fv(glGetUniformLocation(shader.shaderHndel, name), 1, vec);
}

void shaderSetVec4(Shader shader, const char *name, vec4 vec)
{
    glUniform4fv(glGetUniformLocation(shader.shaderHndel, name), 1, vec);
}

void shaderSetMat4(Shader shader, const char *name, mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderHndel, name), 1, GL_FALSE, mat[0]);
}

void deleteShader(Shader* shader)
{
    glDeleteProgram(shader->shaderHndel);
}
