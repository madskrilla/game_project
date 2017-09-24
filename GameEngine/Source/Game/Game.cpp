#include "stdafx.h"
#include <memory>

#include "Game.h"

#include "GameObject.h"
#include "../RenderEngine/Source/RenderEngineInterface.h"
#include "../Utils/ObjectPool.h"

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

}

void CGame::Update(float deltaTime)
{

}
void CGame::Destroy()
{

}