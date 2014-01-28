//Graphics framework
//Created for use with homework for intermediete graphics
//Eric Lemieux, 2014

////Includes
//Standard C++
#include <iostream>

//Graphics
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>

//Project
#include "VertexBuffer.h"
#include "GLSL.h"

//Start
int main(void)
{
	//Create the window
	GLFWwindow* myWindow;

	//init glfw
	if(!glfwInit())
	{
		return -1;
	}

	//Setup the window
	myWindow = glfwCreateWindow(800, 600, "Graphics Framework", NULL, NULL);

	//if the window didnt setup properly close the program.
	if(!myWindow)
	{
		glfwTerminate();
		return -2;
	}

	//Set the window as the current one
	glfwMakeContextCurrent(myWindow);

	//Init GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK)
		std::cout<<"glewInit() Error\n";

	//Init DevIL
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	//Create a test shader
	GLSLProgram *testProgram = new GLSLProgram;
	int result = 1;
	GLSLShader testShader_V, testShader_F;
	result *= testShader_V.CreateShaderFromFile(GLSL_VERTEX_SHADER, "Shaders/passthu_v.glsl");
	result *= testShader_F.CreateShaderFromFile(GLSL_FRAGMENT_SHADER, "Shaders/passthu_f.glsl");
	result *= testProgram->AttachShader(&testShader_V);
	result *= testProgram->AttachShader(&testShader_F);
	result *= testProgram->LinkProgram();
	result *= testProgram->ValidateProgram();

	//Add verticies to an array to be used by VBO
	float verts[] = {0,0,0,1,-1,0,-1,-1,0};

	//Create example VBO to be used by the program
	VertexBuffer *VBO = new VertexBuffer;
	VBO->Initialize(3, false, false);
	VBO->AddVerticies(verts);

	//main program loop
	while(!glfwWindowShouldClose(myWindow))
	{
		//Clear buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Poll events
		glfwPollEvents();

		//Activate the program
		testProgram->Activate();

		//Render to buffer
		VBO->ActivateAndRender();

		//Deactivate the program
		testProgram->Deactivate();

		//Swap buffers
		glfwSwapBuffers(myWindow);
	}

	//Shutdown glfw
	glfwTerminate();

	//exit the program
	return 0;
}