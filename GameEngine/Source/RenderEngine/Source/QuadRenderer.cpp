#include "stdafx.h"
#include "RenderIncludes.h"

#include "QuadRenderer.h"

cQuadRenderer::cQuadRenderer()
{

}
cQuadRenderer::cQuadRenderer(cQuadRenderer& copy)
{

}
cQuadRenderer::~cQuadRenderer()
{

}

void cQuadRenderer::Initialize()
{
	GLfloat pos[] = {
		.5f, -.5f, 0,
		-.5f, -.5f, 0,
		-.5f, .5f, 0,
		.5f, .5f, 0,
		.5f, -.5f, 0,
		-.5f, .5f, 0 };

	GLfloat uvs[] = {
	  1, 0,
	  0, 0,
	  0, 1,
	  1, 1,
	  1, 0,
	  0, 1
	};

	BuildVerts(pos, uvs);
}

void cQuadRenderer::BuildVerts(GLfloat positions[], GLfloat uvs[])
{
	unsigned int numVerts = 6;
	m_vecVerts.resize(numVerts);
	
	for (unsigned int i = 0; i < numVerts; i++)
	{
		for (unsigned int p = 0; p < 3; p++)
		{
			m_vecVerts[i].position[p] = positions[(i * 3) + p];
		}

		for (unsigned int u = 0; u < 2; u++)
		{
			m_vecVerts[i].UV[u] = uvs[(i * 2) + u];
		}
	}
}

void* cQuadRenderer::GetVertexArray()
{
	return &m_vecVerts[0];
}

void cQuadRenderer::UpdateTransform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 trans;

	trans = glm::translate(trans, pos);

	trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

	trans = glm::scale(trans, scale);

	m_matTransform = trans;
}