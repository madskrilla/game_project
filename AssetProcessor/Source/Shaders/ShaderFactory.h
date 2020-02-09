#pragma once
#include <string>
#include <vector>

class ShaderFactory 
{
public:

	ShaderFactory();
	~ShaderFactory();

	int ProcessShaders();
private:
	std::vector<std::string> RetrieveShaderFileNames();

	void ProcessShader(std::string _fileName);
	GLuint CompileShader(const GLchar* _shaderSource, GLenum shaderType);
	void SaveCompiledShaderProgramToFile();
	const std::string LoadShader(std::string _filename);

	std::string m_strShaderFolder;
	GLint m_ShaderProgram;
};
