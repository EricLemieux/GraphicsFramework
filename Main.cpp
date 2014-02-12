//Graphics framework
//Created for use with homework for intermediete graphics
//Eric Lemieux, 2014

//Based on the code created in tutorial with Dan Buckstein.

////Includes
//Standard C++
#include <iostream>

//Graphics
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#undef _UNICODE
#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>

//Project
#include "VertexBuffer.h"
#include "GLSL.h"
#include "BasicShapes.h"
#include "Utilities.h"

//Math
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\euler_angles.hpp>

//Sound
#include "SoundManager.h"

void initOpenGL(GLFWwindow *window);
int loadTexture(const char* filePath);

//Global variables
glm::mat4 modelMat;
glm::mat4 viewMat;
glm::mat4 projectionMat;

glm::mat4 modelViewProjectionMat;

//Global window variables
int windowWidth, windowHeight;

//Global camera variables
static const float camFOV		= 90.0f;
static const float camNearPlane = 0.1f;
static const float camFarPlane	= 100.0f;

//Uniform variables
int MVP;

Object camera;

void updateObjectMatricies(Object *obj)
{
	glm::mat4 modelMatTranslation = glm::translate(glm::mat4(1), obj->position);
	glm::mat4 modelMatRotation = glm::yawPitchRoll(obj->rotation.x, obj->rotation.y, obj->rotation.z);
	modelMat = glm::mat4(modelMatRotation[0], modelMatRotation[1], modelMatRotation[2], modelMatTranslation[3]);
	
	modelViewProjectionMat	= projectionMat * viewMat * modelMat;
}

void Reshape(int width, int height)
{
	projectionMat = glm::perspective(camFOV, (float)width/(float)height, camNearPlane, camFarPlane);
}


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

	//Init OpenGL
	initOpenGL(myWindow);

	//Init DevIL
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
		
	//Create a test shader
	GLSLProgram *testProgram = new GLSLProgram;
	int result = 1;
	GLSLShader testShader_V, testShader_F;
	result *= testShader_V.CreateShaderFromFile(GLSL_VERTEX_SHADER,		"Shaders/passthu_v.glsl");
	result *= testShader_F.CreateShaderFromFile(GLSL_FRAGMENT_SHADER,	"Shaders/passthu_f.glsl");
	result *= testProgram->AttachShader(&testShader_V);
	result *= testProgram->AttachShader(&testShader_F);
	result *= testProgram->LinkProgram();
	result *= testProgram->ValidateProgram();

	//get uniform variables
	MVP		= testProgram->GetUniformLocation("mvp");

	//Create basic cube
	VertexBuffer *cubeVBO = Shapes_Cube();
	Object cubeObj;

	cubeObj.position = glm::vec3(0,0,0);
	camera.position = glm::vec3(0,0,5);

	//main program loop
	while(!glfwWindowShouldClose(myWindow))
	{
		//Clear buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
		//Poll events
		glfwPollEvents();

		//Activate the program
		testProgram->Activate();

		//Update and pass uniform variables.
		if(cubeObj.rotation.x <= 360)
		{
			cubeObj.rotation.x += 0.01f;
			cubeObj.rotation.y += 0.01f;
		}
		else
		{
			cubeObj.rotation.x = cubeObj.rotation.y = 0;
		}

		//Update the camera
		viewMat			= glm::lookAt(camera.position, glm::vec3(0,0,0), glm::vec3(0,1,0));
				
		updateObjectMatricies(&cubeObj);

		glUniformMatrix4fv(MVP, 1, 0, glm::value_ptr(modelViewProjectionMat));
		
		//Render to buffer
		cubeVBO->ActivateAndRender();

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


void initOpenGL(GLFWwindow *window)
{
	//glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.3f,0.9f,1.0f);

	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	Reshape(windowWidth, windowHeight);
}

int loadTexture(const char* filePath)
{
	//load image
	ILuint texName;
	ilGenImages(1, &texName);
	ilBindImage(texName);

	ilLoadImage(filePath);
	ILubyte *bytes	= ilGetData();	
	if(!bytes)
	{
		std::cout<<"error opening image file";

		//Clean up memory
		ilBindImage(0);
		ilDeleteImages(1, &texName);
		return false;
	}
	else
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
	
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Image is now OpenGL's problem
		ilBindImage(0);
		ilDeleteImages(1, &texName);
		return true;
	}
}