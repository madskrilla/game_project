#include "stdafx.h"

#include "Game.h"

#include "../RenderEngine/Source/RenderEngineInterface.h"
#include "GameObject.h"
#include "MoveableObject.h"
#include "PlayerCharacter.h"

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
	AddObject(new CGameObject());
	AddObject(new CPlayerCharacter("mario.jpg"));
}

void CGame::AddObject(CGameObject* newObj)
{
	m_vecGameObjects.push_back(newObj);
	IRenderEngine::GetInstance()->AddRenderObject(newObj->GetRenderer());
}

void CGame::Update(double deltaTime)
{
	for (unsigned int i = 0; i < m_vecGameObjects.size(); i++)
	{
		m_vecGameObjects[i]->Update(deltaTime);
	}
}
void CGame::Destroy()
{
	for (unsigned int i = 0; i < m_vecGameObjects.size(); i++)
	{
		delete m_vecGameObjects[i];
	}
	m_vecGameObjects.clear();

	delete m_pInst;
}