#ifndef CVOXEL_SHADER_H
#define CVOXEL_SHADER_H

#include <glad/gl.h>
#include <cglm/types.h>

typedef struct
{
    GLuint shaderHndel;
} Shader;

Shader createShader(const char* vertPath, const char* fragPath);

void bindShader(Shader shader);
void unbindShader();

void shaderSetFloat(Shader shader, const char* name, float value);
void shaderSetVec3(Shader shader, const char* name, vec3 vec);
void shaderSetVec4(Shader shader, const char* name, vec4 vec);
void shaderSetMat4(Shader shader, const char* name, mat4 mat);

void deleteShader(Shader* shader);

#endif
