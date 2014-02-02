#pragma once

#include <glm\glm.hpp>

struct Object
{
	Object()
	{
		position	= glm::vec3(0);
		rotation	= glm::vec3(0);
		scale		= glm::vec3(1);
	}
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct Light
{
	Light()
	{
		position	= glm::vec3(0);
		colour		= glm::vec3(0);
	}
public:
	glm::vec3 position;
	glm::vec3 colour;
};