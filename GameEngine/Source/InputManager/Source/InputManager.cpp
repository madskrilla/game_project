#include "stdafx.h"
#include "InputManager.h"

#include <GLFW\glfw3.h>

cInputManager* cInputManager::m_pInst = nullptr;
cInputManager* cInputManager::GetInstance()
{
	if (m_pInst == nullptr)
	{
		m_pInst = new cInputManager();
	}
	return m_pInst;
}

#pragma region constructor/ destructor

cInputManager::cInputManager()
{

}

cInputManager::cInputManager(cInputManager& copy)
{

}

cInputManager::~cInputManager()
{

}

#pragma endregion

void cInputManager::Initialize(GLFWwindow* window)
{
	m_pWindow = window;
}

void cInputManager::Destroy()
{
	m_pWindow = nullptr;
	delete m_pInst;
	m_pInst = nullptr;
}

void cInputManager::AddInput(std::string name, int inputKey)
{
	m_mpInput[name] = inputKey;
}

bool cInputManager::CheckInput(std::string name)
{
	int key = m_mpInput[name];
	return glfwGetKey(m_pWindow, key) == GLFW_PRESS;
}