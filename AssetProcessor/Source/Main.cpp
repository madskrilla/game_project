#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include "Shaders/ShaderFactory.h"

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
}

void InitializeOpenGL();

int main()
{
	InitializeOpenGL();

	ShaderFactory * shaderFactory = new ShaderFactory();
	shaderFactory->ProcessShaders();

	delete shaderFactory;
}

void InitializeOpenGL() 
{
	GLFWwindow* window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	window = glfwCreateWindow(1920, 1080, "My Game Engine", nullptr, nullptr);

	glfwSetKeyCallback(window, Key_Callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}