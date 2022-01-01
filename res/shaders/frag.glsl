#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in float Light;

uniform sampler2D texId;

void main()
{
	vec4 color = texture(texId, TexCoord);
	color.xyz *= Light;
	FragColor = color;
}

