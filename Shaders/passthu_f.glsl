#version 330 core

in vertex
{
	vec3 pos;
	vec3 norm;
	vec2 UV;
}data;

void main()
{
	gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0);
}