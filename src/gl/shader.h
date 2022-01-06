#ifndef CVOXEL_SHADER_H
#define CVOXEL_SHADER_H

#include <stddef.h>
#include <glad/gl.h>

#include <cglm/types-struct.h>

typedef GLuint Shader;

typedef struct
{
	GLuint index;
	const char *name;
} ShaderAttrib;

Shader shaderInit(const char *vpath, const char *fpath, size_t count, ShaderAttrib attrib[]);

void shaderBind(Shader shader);

void shaderUnbind();

void shaderSetFloat(Shader shader, const char *name, float value);

void shaderSetVector2(Shader shader, const char *name, vec2s data);

void shaderSetVector3(Shader shader, const char *name, vec3s data);

void shaderSetVector4(Shader shader, const char *name, vec4s data);

void shaderSetMatrix4(Shader shader, const char *name, mat4s data);

void shaderDelete(Shader shader);

#endif // CVOXEL_SHADER_H
