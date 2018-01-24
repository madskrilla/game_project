#include "stdafx.h"

#include "Game.h"

#include "../RenderEngine/Source/RenderEngineInterface.h"
#include "GameObject.h"

CGame* CGame::m_pInst = nullptr;
CGame* CGame::GetInstance()
{
	if (m_pInst == nullptr)
	{
		m_pInst = new CGame();
	}

	return m_pInst;
}

CGame::CGame()
{

}

CGame::CGame(CGame& copy)
{

}

CGame::~CGame()
{

}

void CGame::Initialize()
{
	CGameObject* background = new CGameObject();
	IRenderEngine::GetInstance()->AddRenderObject(background->GetRenderer());
	
	m_vecGameObjects.push_back(background);
}

void CGame::Update(float deltaTime)
{
	for (unsigned int i = 0; i < m_vecGameObjects.size(); i++)
	{
		m_vecGameObjects[i]->Update(deltaTime);
	}
}
void CGame::Destroy()
{

}