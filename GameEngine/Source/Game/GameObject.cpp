#include "stdafx.h"
#include "GameObject.h"

#include "../RenderEngine/Source/IRenderer.h"
#include "../RenderEngine/Source/QuadRenderer.h"

CGameObject::CGameObject()
{
	m_vecScale =	{ 1, 1, 1 };
	m_vecPosition = { 0, 0, 0 };
	m_vecRotation = { 0, 0, 0 };

	m_pRenderer = new cQuadRenderer();
	m_pRenderer->Initialize();
	m_pRenderer->SetTextureName("wall.jpg");
}

CGameObject::CGameObject(CGameObject& copy)
{

}

CGameObject::~CGameObject()
{
	delete m_pRenderer;
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_vecPosition = { x,y,z };
}

void CGameObject::SetRotation(float x, float y, float z)
{
	m_vecRotation = { x,y,z };
}

void CGameObject::SetScale(float x, float y, float z)
{
	m_vecScale = { x,y,z };
}

void CGameObject::Update(float deltaTime)
{
	m_pRenderer->UpdateTransform(m_vecPosition, m_vecRotation, m_vecScale);
}