#pragma once

#include "RenderIncludes.h"

struct Assimp_Vertex;
struct Texture;

class CMesh
{
public:
	CMesh();
	~CMesh();

	void BuildMesh(std::vector<Assimp_Vertex> verts, std::vector<unsigned int> indicies, std::vector<Texture> textures);
	//void Draw(Shader shader);
private:

	std::vector<Assimp_Vertex> m_vecVerts;
	std::vector<unsigned int> m_vecIdecies;
	std::vector<Texture> m_vecTextures;
};

