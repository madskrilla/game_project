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
	bool Update();

	static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	double GetDeltaTime() { return m_dDeltaTime; }
	//Members
	static IRenderEngine* GetInstance();
	void AddRenderObject(IRenderer* obj);
private:
	//Methods
	GLFWwindow* CreateNewWindow();
	void UpdateFPSCounter();
	double DeltaTime();
	//Members
	GLFWwindow* m_pWindow;
	CRenderContext* m_pRenderContext;
	double m_dTimeLast;
	double m_dDeltaTime;
	double m_dFPSTimer;
	int m_nFrames;

};
