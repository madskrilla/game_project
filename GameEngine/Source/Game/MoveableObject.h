#pragma once
#include "GameObject.h"

class cMovableObject : public CGameObject
{
public:

	cMovableObject();
	cMovableObject(std::string texture);
	cMovableObject(cMovableObject&) {};
	virtual ~cMovableObject();

	void Update(float deltaTime) override;

protected:

	float m_fAccel, m_fMaxSpeed, m_fSlowDown;
	glm::vec3 m_vecVelocity;
};