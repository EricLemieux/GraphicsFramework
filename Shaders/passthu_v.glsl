#version 330 core

in vec4 position;

uniform mat4 mvp;


void main()
{
	gl_Position = mvp * position;
	//gl_Position = mvp * gl_Vertex;
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//gl_Position = gl_ModelViewProjectionMatrix * position;
}