#include "stdafx.h"
#include "GameObject.h"

#include "../RenderEngine/Source/RenderNode.h"

CGameObject::CGameObject()
{
	m_strTexture = "container.jpg";
	m_vecScale = { 1,1,1 };
}

CGameObject::CGameObject(CGameObject& copy)
{

}

CGameObject::~CGameObject()
{

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
	m_pRenderNode->UpdateNode(m_vecPosition, m_vecRotation, m_vecScale);
}