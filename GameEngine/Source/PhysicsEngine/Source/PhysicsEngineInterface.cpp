#include "stdafx.h"

#include "PhysicsEngineInterface.h"

IPhysicsEngine* IPhysicsEngine::m_pInst = nullptr;
IPhysicsEngine* IPhysicsEngine::GetInstance()
{
	if (m_pInst == nullptr)
	{
		m_pInst = new IPhysicsEngine();
	}

	return m_pInst;
}

void IPhysicsEngine::Initialize()
{
}
void IPhysicsEngine::Destroy()
{
}
void IPhysicsEngine::Update(float deltaTime)
{
}