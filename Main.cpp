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

void initOpenGL(GLFWwindow *window);
int loadTexture(const char* filePath);

//Global variables
glm::mat4 modelMat;
glm::mat4 viewMat;
glm::mat4 projectionMat;

glm::mat4 modelViewMat;
glm::mat4 viewProjectionMat;
glm::mat4 modelViewProjectionMat;

glm::mat4 eyeToWorld;
glm::mat4 worldToObject;

//Uniform variables
int vertMV, vertMVP;

Object camera;

glm::mat4 lookAt(Object *obj, glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	glm::mat4 newMat;

	obj->position = position;
	newMat[3] = glm::vec4(position,1);

	newMat[2] = glm::vec4(glm::normalize(position - target),0);

	newMat[0] = glm::vec4(glm::normalize(glm::cross( worldUp, glm::vec3(newMat[2].x,newMat[2].y,newMat[2].z))),0);

	newMat[1] = glm::vec4(glm::normalize(glm::cross( glm::vec3(newMat[2].x,newMat[2].y,newMat[2].z), glm::vec3(newMat[0].x,newMat[0].y,newMat[0].z))),0);

	return newMat;
}

glm::mat4 transformInverseUniformScale(glm::mat4 mat)
{
	glm::mat4 result;

	result = glm::mat4(glm::transpose(glm::mat3(mat)) * (1/glm::dot(glm::vec3(mat[0]), glm::vec3(mat[0]))));

	result[3] = -result[3];

	return result;
}

glm::mat4 transformInverseNoScale(glm::mat4 mat)
{
	glm::mat4 result;

	glm::mat3 temp = glm::mat3(eyeToWorld[0].x, eyeToWorld[0].y, eyeToWorld[0].z,
								eyeToWorld[1].x, eyeToWorld[1].y, eyeToWorld[1].z,
								eyeToWorld[2].x, eyeToWorld[2].y, eyeToWorld[2].z);
	temp = glm::transpose(temp);

	glm::vec3 m = glm::vec3(mat[3].x, mat[3].y, mat[3].z);
	glm::vec4 r = glm::vec4(-(temp * m),1);

	result = glm::mat4(glm::vec4(temp[0],0), glm::vec4(temp[1],0), glm::vec4(temp[2],0), r);

	//result[3] = -result[3];

	return result;
}

void updateObjectMatricies(Object *obj)
{
	modelMat = glm::yawPitchRoll(obj->rotation.x, obj->rotation.y, obj->rotation.z);
	//modelMat *= obj->scale;
	glm::scale(modelMat,obj->scale);
	modelMat = glm::mat4(modelMat[0], modelMat[1], modelMat[2], glm::vec4(obj->position,1));

	modelViewMat = viewMat * modelMat;

	modelViewProjectionMat = modelViewMat * projectionMat;

	worldToObject = transformInverseUniformScale(modelMat);
}

void updateCameraMatricies(void)
{
	viewMat = transformInverseNoScale(eyeToWorld);

	viewProjectionMat = projectionMat * viewMat;
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
	vertMV		= testProgram->GetUniformLocation("mv");
	vertMVP		= testProgram->GetUniformLocation("mvp");

	//Create basic cube
	VertexBuffer *cubeVBO = Shapes_Cube();
	Object cubeObj;

	//main program loop
	while(!glfwWindowShouldClose(myWindow))
	{
		//Clear buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Update the camera
		eyeToWorld = lookAt(&camera, camera.position, camera.position + glm::vec3(0,0,1), glm::vec3(0,1,0));
		updateCameraMatricies();

		//Update positions in world space
		glm::vec4 eyePosWorld = glm::vec4(camera.position, 1.0f);

		//positions in object space
		glm::vec4 eyePosObj;

		//Poll events
		glfwPollEvents();
		
		//Activate the program
		testProgram->Activate();

		//Update and pass uniform variables.
		updateObjectMatricies(&cubeObj);
		glUniformMatrix4fv(vertMVP, 1, 0, glm::value_ptr(modelViewProjectionMat));
		

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
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f,0.9f,1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	gluPerspective(90.0f, (double)width/(double)height, 0.0f, 1000.0f);
	
	glMatrixMode(GL_MODELVIEW);
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