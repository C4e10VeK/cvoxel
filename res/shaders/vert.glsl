#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float aLight;

uniform mat4 model, view, proj;

out vec2 TexCoord;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
}

