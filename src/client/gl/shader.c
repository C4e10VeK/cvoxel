#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../utils/types.h"

#ifdef _WIN32
#define FILE_OPEN(fn, mode) ({	FILE* f = NULL;\
								i32 err = fopen_s(&f, fn, mode);\
								assert(!err);\
								f;})
#else
#define FILE_OPEN(fn, mode) fopen(fn, mode)
#endif

typedef void (*GLget)(GLuint, GLenum, GLint *);
typedef void (*GLinfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);

static void _checkError(GLuint glHandle, GLenum status, const GLget get, const GLinfoLog infoLog)
{
	char log[1024];
	i32 success;

	get(glHandle, status, &success);

	if (!success)
	{
		infoLog(glHandle, 1024, NULL, log);
		printf("%s\n", log);
		abort();
	}
}

static GLuint _compileShader(const char *shaderPath, GLenum type)
{	
	assert(shaderPath && "Shader path is null\n");
	
	GLuint shaderProgram;
	i32 length;
	char *code = NULL;

	FILE *file = FILE_OPEN(shaderPath, "rb");
	assert(file && "Failed to open file\n");

	fseek(file, 0, SEEK_END);
	length = ftell(file);

	assert(length > 0);

	fseek(file, 0, SEEK_SET);
	code = calloc(sizeof(char), length);
	assert(code);

	fread(code, 1, length, file);

	shaderProgram = glCreateShader(type);
	glShaderSource(shaderProgram, 1, (const char* const*)&code, &length);
	glCompileShader(shaderProgram);

	_checkError(shaderProgram, GL_COMPILE_STATUS, glGetShaderiv, glGetShaderInfoLog);

	fclose(file);
	free(code);

	return shaderProgram;
}

Shader shaderInit(const char *vpath, const char *fpath, size_t count, ShaderAttrib attrib[])
{
	GLuint vs = _compileShader(vpath, GL_VERTEX_SHADER);
	GLuint fs = _compileShader(fpath, GL_FRAGMENT_SHADER);

	Shader shader = glCreateProgram();

	glAttachShader(shader, vs);
	glAttachShader(shader, fs);

	glLinkProgram(shader);

	_checkError(shader, GL_LINK_STATUS, glGetProgramiv, glGetProgramInfoLog);

	for (size_t i = 0; i < count; i++)
	{
		glBindAttribLocation(shader, attrib[i].index, attrib[i].name);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shader;
}

void shaderBind(Shader shader)
{
	glUseProgram(shader);
}

void shaderUnbind()
{
	glUseProgram(0);
}

void shaderSetFloat(Shader shader, const char *name, float value)
{
	glUniform1f(glGetUniformLocation(shader, name), value);
}

void shaderSetVector2(Shader shader, const char *name, vec2s data)
{
	glUniform2f(glGetUniformLocation(shader, name), data.x, data.y);
}

void shaderSetVector3(Shader shader, const char *name, vec3s data)
{
	glUniform3f(glGetUniformLocation(shader, name), data.x, data.y, data.z);
}

void shaderSetVector4(Shader shader, const char *name, vec4s data)
{
	glUniform4f(glGetUniformLocation(shader, name), data.x, data.y, data.z, data.w);
}

void shaderSetMatrix4(Shader shader, const char *name, mat4s data)
{
	glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, data.raw[0]);
}

void shaderDelete(Shader shader)
{
	glDeleteProgram(shader);
}

