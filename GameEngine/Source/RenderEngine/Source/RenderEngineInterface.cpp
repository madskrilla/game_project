/*
	RenderEngineInterface.cpp

	Purpose:
	Interface for the other modules to interact with the render engine

	Last Modified:
	2/6/2018
	Reason:
	Adding Comments
*/
#include "stdafx.h"
#include "RenderEngineInterface.h"

#include "RenderIncludes.h"
#include "RenderContext.h"
#include "IRenderer.h"
#include "Camera.h"
#include "../../Game/GameObject.h"
#include "../../InputManager/Source/InputManager.h"

#define WIDTH 1920;
#define HEIGHT 1080;

IRenderEngine* IRenderEngine::m_pInst = nullptr;
IRenderEngine* IRenderEngine::GetInstance()
{
	if (m_pInst == nullptr)
	{
		m_pInst = new IRenderEngine();
	}

	return m_pInst;
}

void IRenderEngine::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

/*
	Initialize()
	Summary:
	Initialize All Internal RenderEngine Components
*/
void IRenderEngine::Initialize()
{
	m_pWindow = CreateNewWindow();

	m_pRenderContext = new CRenderContext();
	m_pRenderContext->SetCamera(new CCamera());
	m_pRenderContext->Initialize();

	cInputManager::GetInstance()->Initialize(m_pWindow);

	m_fTimeLast = 0;
}

/*
	CreateWindow()
	Summary:
	Creates a new OpenGl Window
*/
GLFWwindow* IRenderEngine::CreateNewWindow()
{
	GLFWwindow* window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(1920, 1080, "My Game Engine", nullptr, nullptr);

	glfwSetKeyCallback(window, Key_Callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	return window;
}

/*
	AddRenderObject()
	Summary:
	Adds a new renderObject to the render engine

	TODO:
	Add functionality for multiple render sets
*/
void IRenderEngine::AddRenderObject(IRenderer* obj)
{
	m_pRenderContext->AddRenderObject(obj, obj->GetNumIndicies());
}

/*
	DeltaTime()
	Summary:
	Determines the time between frames
*/
float IRenderEngine::DeltaTime()
{
	float currTime = (float)glfwGetTime();
	float delta = currTime - m_fTimeLast;
	m_fTimeLast = currTime;
	return delta;
}

/*
	Update()
	Summary:
	Clear the render buffer
	Render objects in the RenderSet
	Swap front buffer
*/
bool IRenderEngine::Update()
{
	if (!glfwWindowShouldClose(m_pWindow))
	{
#pragma region renderCode
		glClearColor(0.0f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_pRenderContext->Render();
#pragma endregion

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();

		return true;
	}
	return false;
}

/*
	Destroy()
	Summary:
	Deallocate any memory allocated by the render interface
*/
void IRenderEngine::Destroy()
{
	cInputManager::GetInstance()->Destroy();

	//Deallocate Memory
	m_pRenderContext->Destroy();
	delete m_pRenderContext;

	//terminate openGL
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();

	//Delete Instance Pointer
	delete m_pInst;
	m_pInst = nullptr;
}