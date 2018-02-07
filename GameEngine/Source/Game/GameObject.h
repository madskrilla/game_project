#pragma once
#include "../RenderEngine/Source/RenderIncludes.h"

class CGameObject
{
public:
	CGameObject();
	CGameObject(CGameObject& copy);
	virtual ~CGameObject();

	virtual void Update(float deltaTime);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	IRenderer* GetRenderer() { return m_pRenderer; }

protected:

	IRenderer* m_pRenderer;
	std::string m_strTexture;

	glm::vec3 m_vecPosition;
	glm::vec3 m_vecRotation;
	glm::vec3 m_vecScale;
};
