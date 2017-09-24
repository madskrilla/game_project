#include "stdafx.h"
#include "RenderEngineInterface.h"

#include "RenderIncludes.h"
#include "RenderContext.h"
#include "Vertex.h"
#include "Camera.h"
#include "../../Game/GameObject.h"

#define WIDTH 600;
#define HEIGHT 800;

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
Initialize All Internal RenderEngine Components
*/
void IRenderEngine::Initialize()
{
	m_pWindow = CreateNewWindow();

	m_pRenderContext = new CRenderContext();
	m_pRenderContext->SetCamera(new CCamera());
	m_pRenderContext->Initialize();

	m_fTimeLast = 0;

	for (unsigned int i = 0; i < 6; i++)
	{
		m_lstQuadVerts.push_back(new CVertex());
	}

	m_lstQuadVerts[0]->SetPosition(.5f, -.5f, 0);
	m_lstQuadVerts[0]->SetTexCoords(1, 0);

	m_lstQuadVerts[1]->SetPosition(-.5f, -.5f, 0);
	m_lstQuadVerts[1]->SetTexCoords(0, 0);
					 
	m_lstQuadVerts[2]->SetPosition(-.5f, .5f, 0);
	m_lstQuadVerts[2]->SetTexCoords(0, 1);
					
	m_lstQuadVerts[3]->SetPosition(.5f, .5f, 0);
	m_lstQuadVerts[3]->SetTexCoords(1, 1);
				
	m_lstQuadVerts[4]->SetPosition(.5f, -.5f, 0);
	m_lstQuadVerts[4]->SetTexCoords(1.0f, 0);
					
	m_lstQuadVerts[5]->SetPosition(-.5f, .5f, 0);
	m_lstQuadVerts[5]->SetTexCoords(0, 1);
}

GLFWwindow* IRenderEngine::CreateNewWindow()
{
	GLFWwindow* window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "My Game Engine", nullptr, nullptr);

	glfwSetKeyCallback(window, Key_Callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	return window;
}

void IRenderEngine::AddRenderObject(CGameObject* obj)
{
	m_pRenderContext->CreateRenderNode(m_lstQuadVerts, obj);
}

float IRenderEngine::DeltaTime()
{
	float currTime = (float)glfwGetTime();
	float delta = currTime - m_fTimeLast;
	m_fTimeLast = currTime;
	return delta;
}

/*
Update And Render Objects
*/
bool IRenderEngine::Update(float dt)
{
	if (!glfwWindowShouldClose(m_pWindow))
	{
#pragma region renderCode
		glClearColor(0.0f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_pRenderContext->Render(dt);
#pragma endregion

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();

		return true;
	}
	return false;
}

/*
Destroy Render Engine Components
*/
void IRenderEngine::Destroy()
{
	//Deallocate Memory
	m_pRenderContext->Destroy();
	delete m_pRenderContext;

	//terminate openGL
	glfwTerminate();

	//Delete Instance Pointer
	delete m_pInst;
	m_pInst = nullptr;
}