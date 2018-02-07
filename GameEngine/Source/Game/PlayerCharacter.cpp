#include "stdafx.h"
#include "PlayerCharacter.h"

#include <string>
#include "../RenderEngine/Source/QuadRenderer.h"
#include "../InputManager/Source/InputManager.h"

CPlayerCharacter::CPlayerCharacter()
{

}

CPlayerCharacter::CPlayerCharacter(std::string texture)
{
	m_vecScale = { 0.25, 0.25, 1 };
	m_vecPosition = { 0, 0, 0 };
	m_vecRotation = { 0, 0, 0 };
	m_vecVelocity = { 0, 0, 0 };

	m_fAccel = 0.4f;
	m_fMaxSpeed = 7.0f;
	m_fSlowDown = 0.75f;

	m_pRenderer->SetTextureName(texture);

	m_pInputManager = cInputManager::GetInstance();

	m_pInputManager->AddInput("right", GLFW_KEY_D);
	m_pInputManager->AddInput("left", GLFW_KEY_A);
}

CPlayerCharacter::~CPlayerCharacter()
{

}

void CPlayerCharacter::Update(float deltaTime)
{
	if (m_pInputManager->CheckInput("right"))
	{
		m_vecVelocity.x += m_fAccel;
	}
	else if (m_pInputManager->CheckInput("left"))
	{
		m_vecVelocity.x -= m_fAccel;
	}


	cMovableObject::Update(deltaTime);
}