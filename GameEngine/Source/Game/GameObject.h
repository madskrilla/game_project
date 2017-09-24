#pragma once
#include "../RenderEngine/Source/RenderIncludes.h"

class CRenderNode;

class CGameObject
{
public:
	CGameObject();
	CGameObject(CGameObject& copy);
	virtual ~CGameObject();

	virtual std::string GetTexture() { return m_strTexture; }
	virtual void Update(float deltaTime);

	void SetRenderNode(CRenderNode* node) { m_pRenderNode = node; }
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

protected:

	CRenderNode* m_pRenderNode;
	std::string m_strTexture;

	glm::vec3 m_vecPosition;
	glm::vec3 m_vecRotation;
	glm::vec3 m_vecScale;
};
