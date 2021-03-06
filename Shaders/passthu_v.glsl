#version 330 core

layout (location=0) in vec4 position;
layout (location=2) in vec3 normal;
layout (location=8) in vec2 texcoord;

uniform mat4 mvp;

out vertex
{
	vec3 pos;
	vec3 norm;
	vec2 UV;
}data;

void main()
{
	gl_Position = mvp * position;

	data.pos	= position.xyz;
	data.norm	= normal;
	data.UV		= texcoord;
}