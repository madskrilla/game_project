#pragma once
#include "RenderIncludes.h"

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct VERT_POS_UV
{
public:
	GLfloat position[3];
	GLfloat UV[2];

	bool VERT_POS_UV::operator==(VERT_POS_UV& rght)
	{
		GLfloat * rghtPosition = rght.position;
		GLfloat * rightUVs = rght.UV;

		for (unsigned int i = 0; i < 3; i++)
		{
			if (rghtPosition[i] != position[i])
			{
				return false;
			}

			if (i < 2 && rightUVs[i] != UV[i])
			{
				return false;
			}
		}

		return true;
	}
};

struct Assimp_Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	std::vector<glm::vec3> texCoords;
};

struct Texture
{
	int width, height, numChannels;
	std::string name;
};
