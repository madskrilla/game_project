#pragma once

//Forward Declarations
class CRenderContext;
class CGameObject;
struct GLFWwindow;
class IRenderer;

class IRenderEngine
{
#pragma region Singleton
private:
	//Methods
	IRenderEngine() {};
	IRenderEngine(IRenderEngine&) {};
	~IRenderEngine() {};
	//Members
	static IRenderEngine* m_pInst;
#pragma endregion

public:
	//Methods
	void Initialize();
	void Destroy();
	bool Update(float deltaTime);

	static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	float DeltaTime();

	//Members
	static IRenderEngine* GetInstance();
	void AddRenderObject(IRenderer* obj);
private:
	//Methods
	GLFWwindow* CreateNewWindow();
	//Members
	GLFWwindow* m_pWindow;
	CRenderContext* m_pRenderContext;
	float m_fTimeLast;

};
