#pragma once
#include "IRenderer.h"

class cQuadRenderer : public IRenderer
{
public:
	cQuadRenderer();
	cQuadRenderer(cQuadRenderer& copy);
	virtual ~cQuadRenderer();

	virtual void Initialize();
	virtual void* GetVertexArray();
	virtual void UpdateTransform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale);

	virtual const unsigned int GetNumIndicies() { return m_vecVerts.size(); }
	
private:
	std::vector<VERT_POS_UV> m_vecVerts;

	void BuildVerts(GLfloat positions[], GLfloat uvs[]);
};