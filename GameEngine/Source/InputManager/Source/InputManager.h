#pragma once

#include <map>

struct GLFWwindow;

class cInputManager
{
private:
	cInputManager();
	cInputManager(cInputManager& copy);
	~cInputManager();

	static cInputManager* m_pInst;
public:

	static cInputManager* GetInstance();

	void Initialize(GLFWwindow* window);
	void Destroy();

	void AddInput(std::string name, int inputKey);
	bool CheckInput(std::string name);

private:

	GLFWwindow* m_pWindow;
	std::map<std::string, int>	m_mpInput;
};