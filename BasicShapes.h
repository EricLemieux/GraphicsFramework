//Creates basic shapes for testing on.

#pragma once

#include <fstream>
#include <vector>

#include "VertexBuffer.h"

//Basic Cube
inline VertexBuffer* Shapes_Cube(void)
{
	VertexBuffer *cube = new VertexBuffer;
	
	float verts[]	= { -0.5f, -0.5f,  0.5f,	// +z
						 0.5f, -0.5f,  0.5f, 
						-0.5f,  0.5f,  0.5f, 
						-0.5f,  0.5f,  0.5f, 
						 0.5f, -0.5f,  0.5f, 
						 0.5f,  0.5f,  0.5f, 

						-0.5f,  0.5f, -0.5f,	// -z
						 0.5f,  0.5f, -0.5f, 
						-0.5f, -0.5f, -0.5f, 
						-0.5f, -0.5f, -0.5f, 
						 0.5f,  0.5f, -0.5f, 
						 0.5f, -0.5f, -0.5f, 

						 0.5f, -0.5f,  0.5f,	// +x
						 0.5f, -0.5f, -0.5f, 
						 0.5f,  0.5f,  0.5f, 
						 0.5f,  0.5f,  0.5f, 
						 0.5f, -0.5f, -0.5f, 
						 0.5f,  0.5f, -0.5f, 

						-0.5f, -0.5f, -0.5f,	// -x
						-0.5f, -0.5f,  0.5f, 
						-0.5f,  0.5f, -0.5f, 
						-0.5f,  0.5f, -0.5f, 
						-0.5f, -0.5f,  0.5f, 
						-0.5f,  0.5f,  0.5f, 

						-0.5f,  0.5f,  0.5f,	// +y
						 0.5f,  0.5f,  0.5f, 
						-0.5f,  0.5f, -0.5f, 
						-0.5f,  0.5f, -0.5f, 
						 0.5f,  0.5f,  0.5f, 
						 0.5f,  0.5f, -0.5f, 

						-0.5f, -0.5f, -0.5f,	// -y
						 0.5f, -0.5f, -0.5f, 
						-0.5f, -0.5f,  0.5f, 
						-0.5f, -0.5f,  0.5f, 
						 0.5f, -0.5f, -0.5f, 
						 0.5f, -0.5f,  0.5f, 
	};

	float normals[]	= {  0.0f,  0.0f,  1.0f,	// +z
						 0.0f,  0.0f,  1.0f, 
						 0.0f,  0.0f,  1.0f, 
						 0.0f,  0.0f,  1.0f, 
						 0.0f,  0.0f,  1.0f, 
						 0.0f,  0.0f,  1.0f, 
			 
						 0.0f,  0.0f, -1.0f, 	// -z
						 0.0f,  0.0f, -1.0f, 
						 0.0f,  0.0f, -1.0f, 
						 0.0f,  0.0f, -1.0f, 
						 0.0f,  0.0f, -1.0f, 
						 0.0f,  0.0f, -1.0f, 
			 
						 1.0f,  0.0f,  0.0f, 	// +x
						 1.0f,  0.0f,  0.0f, 
						 1.0f,  0.0f,  0.0f, 
						 1.0f,  0.0f,  0.0f, 
						 1.0f,  0.0f,  0.0f, 
						 1.0f,  0.0f,  0.0f, 
			
						-1.0f,  0.0f,  0.0f, 	// -x
						-1.0f,  0.0f,  0.0f, 
						-1.0f,  0.0f,  0.0f, 
						-1.0f,  0.0f,  0.0f, 
						-1.0f,  0.0f,  0.0f, 
						-1.0f,  0.0f,  0.0f, 
			 
						 0.0f,  1.0f,  0.0f, 	// +y
						 0.0f,  1.0f,  0.0f, 
						 0.0f,  1.0f,  0.0f, 
						 0.0f,  1.0f,  0.0f, 
						 0.0f,  1.0f,  0.0f, 
						 0.0f,  1.0f,  0.0f, 
			
						 0.0f, -1.0f,  0.0f, 	// -y
						 0.0f, -1.0f,  0.0f, 
						 0.0f, -1.0f,  0.0f, 
						 0.0f, -1.0f,  0.0f, 
						 0.0f, -1.0f,  0.0f, 
						 0.0f, -1.0f,  0.0f, 
	};

	float texCoords[]= { 0.375f, 0.00f,			// +z
						 0.625f, 0.00f, 
						 0.375f, 0.25f, 
						 0.375f, 0.25f, 
						 0.625f, 0.00f, 
						 0.625f, 0.25f, 
						 
						 0.375f, 0.50f,			// -z
						 0.625f, 0.50f, 
						 0.375f, 0.75f, 
						 0.375f, 0.75f, 
						 0.625f, 0.50f, 
						 0.625f, 0.75f, 
						 
						 0.625f, 0.00f,			// +x
						 0.875f, 0.00f, 
						 0.625f, 0.25f, 
						 0.625f, 0.25f, 
						 0.875f, 0.00f, 
						 0.875f, 0.25f, 
						 
						 0.125f, 0.00f,			// -x
						 0.375f, 0.00f, 
						 0.125f, 0.25f, 
						 0.125f, 0.25f, 
						 0.375f, 0.00f, 
						 0.375f, 0.25f, 
						 
						 0.375f, 0.25f,			// +y
						 0.625f, 0.25f, 
						 0.375f, 0.50f, 
						 0.375f, 0.50f, 
						 0.625f, 0.25f, 
						 0.625f, 0.50f, 
						 
						 0.375f, 0.75f,			// -y
						 0.625f, 0.75f, 
						 0.375f, 1.00f, 
						 0.375f, 1.00f, 
						 0.625f, 0.75f, 
						 0.625f, 1.00f,  };

	cube->Initialize(36, true, true);
	cube->AddVerticies(verts);
	cube->AddNormals(normals);
	cube->AddTexCoords(texCoords);

	return cube;
}

//basic ball to test on
inline VertexBuffer* Shapes_Plane(void)
{
	VertexBuffer *plane = new VertexBuffer;
	
	float verts[]	= { -0.5f, -0.5f,  0.0f, 
						 0.5f, -0.5f,  0.0f, 
						-0.5f,  0.5f,  0.0f, 
						-0.5f,  0.5f,  0.0f, 
						 0.5f, -0.5f,  0.0f, 
						 0.5f,  0.5f,  0.0f, 
	};

	float normals[]	= { 0.0f, 0.0f, 1.0f, 
						0.0f, 0.0f, 1.0f, 
						0.0f, 0.0f, 1.0f, 
						0.0f, 0.0f, 1.0f, 
						0.0f, 0.0f, 1.0f, 
						0.0f, 0.0f, 1.0f, 
	};

	float texCoords[]= {0.0f, 0.0f, 
						1.0f, 0.0f, 
						0.0f, 1.0f, 
						0.0f, 1.0f, 
						1.0f, 0.0f, 
						1.0f, 1.0f, 
	};

	plane->Initialize(6, true, true);
	plane->AddVerticies(verts);
	plane->AddNormals(normals);
	plane->AddTexCoords(texCoords);

	return plane;
}

//Load shapes from file to test on
inline VertexBuffer* Shapes_Load(char* fileName)
{
	VertexBuffer *newShape = new VertexBuffer();
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	std::vector<int> facesVerts;
	std::vector<int> facesTexCoords;
	std::vector<int> facesNormals;


	char* firstWord		= new char();
	char* data			= new char();

	//Open the file
	std::ifstream file;
	file.open(fileName);
	if(!file.is_open())
	{
		std::cout<<"Error opening the file "<<fileName<<"\n";
		return NULL;
	}

	//Load data
	while(!file.eof())
	{
		file>>firstWord;

		//Vertex data
		if(!_stricmp(firstWord,"v"))
		{
			glm::vec3 vertex;

			//X data
			file>>data;
			vertex.x = atof(data);

			//Y data
			file>>data;
			vertex.y = atof(data);

			//Z data
			file>>data;
			vertex.z = atof(data);

			verts.push_back(vertex);
		}
		//Tex coord data
		else if(!_stricmp(firstWord,"vt"))
		{
			glm::vec2 texCoord;

			//X data
			file>>data;
			texCoord.x = atof(data);

			//Y data
			file>>data;
			texCoord.y = atof(data);

			texCoords.push_back(texCoord);
		}

		//normals data
		else if(!_stricmp(firstWord,"vn"))
		{
			glm::vec3 normal;

			//X data
			file>>data;
			normal.x = atof(data);

			//Y data
			file>>data;
			normal.y = atof(data);

			//Z data
			file>>data;
			normal.z = atof(data);

			normals.push_back(normal);
		}

		//faces data
		else if(!_stricmp(firstWord,"f"))
		{
			for(unsigned int i = 0; i < 3; ++i)
			{
				int facesArray[3];

				for(unsigned int i = 0; i < 3; ++i)
				{
					if( i == 2)
						file>>data;
					else
						file.getline(data, 256, '/');
					facesArray[i] = atoi(data);
				}

				facesVerts.push_back(facesArray[0]-1);
				facesTexCoords.push_back(facesArray[1]-1);
				facesNormals.push_back(facesArray[2]-1);
			}
		}

		//skip to the end of the line
		file.ignore(256,'\n');
	}

	//create vertex data for faces
	//float* finalVerts[];
	std::vector<float> finalVerts;
	for(unsigned int i = 0; i < facesVerts.size(); ++i)
	{
		finalVerts.push_back(verts[facesVerts[i]].x);
		finalVerts.push_back(verts[facesVerts[i]].y);
		finalVerts.push_back(verts[facesVerts[i]].z);
	}

	//std::vector<float> finalTexCoords;
	//for(unsigned int i = 0; i < facesTexCoords.size(); ++i)
	//{
	//	finalTexCoords.push_back(texCoords[facesTexCoords[i]].x);
	//	finalTexCoords.push_back(texCoords[facesTexCoords[i]].y);
	//}

	std::vector<float> finalTexCoords;
	for(unsigned int i = 0; i < facesTexCoords.size(); ++i)
	{
		finalTexCoords.push_back(texCoords[facesTexCoords[i]].x);
		finalTexCoords.push_back(texCoords[facesTexCoords[i]].y);
	}

	std::vector<float> finalNormals;
	for(unsigned int i = 0; i < facesNormals.size(); ++i)
	{
		finalNormals.push_back(normals[facesNormals[i]].x);
		finalNormals.push_back(normals[facesNormals[i]].y);
		finalNormals.push_back(normals[facesNormals[i]].z);
	}

	//Init and add data
	newShape->Initialize(finalVerts.size()/3, false, false);
	newShape->AddVerticies(&finalVerts[0]);
	newShape->AddNormals(&finalNormals[0]);
	newShape->AddTexCoords(&finalTexCoords[0]);

	//return vbo
	return newShape;
}