#include "stdafx.h"
#include "Mesh.h"
#include "RenderStructs.h"


CMesh::CMesh()
{
}


CMesh::~CMesh()
{
}

void CMesh::BuildMesh(std::vector<Assimp_Vertex> verts, std::vector<unsigned int> indicies, std::vector<Texture> textures)
{
	m_vecVerts = verts;
	m_vecIdecies = indicies;
	m_vecTextures = textures;
}
