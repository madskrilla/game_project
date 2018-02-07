#include "stdafx.h"
#include "MoveableObject.h"

#include <string>
#include "../RenderEngine/Source/QuadRenderer.h"
#include "../InputManager/Source/InputManager.h"

#include<glm/gtx/norm.hpp>

cMovableObject::cMovableObject() 
{

}

cMovableObject::cMovableObject(std::string texture)
{
	m_vecScale =	{ 0.25, 0.25, 1 };
	m_vecPosition = { 0, 0, 0 };
	m_vecRotation = { 0, 0, 0 };
	m_vecVelocity = { 0, 0, 0 };

	m_pRenderer->SetTextureName(texture);
}

cMovableObject::~cMovableObject()
{

}

void cMovableObject::Update(float deltaTime)
{
	float length = glm::length2(m_vecVelocity);

	if (length > m_fMaxSpeed)
	{
		glm::normalize(m_vecVelocity);
	}
	m_vecPosition += m_vecVelocity * deltaTime;
	m_vecVelocity *= m_fSlowDown;
	if (length < 0.1f)
	{
		m_vecVelocity = { 0,0,0 };
	}

	CGameObject::Update(deltaTime);
}