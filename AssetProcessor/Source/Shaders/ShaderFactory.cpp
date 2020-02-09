#include <Windows.h>
#define LEAN_AND_MEAN

//Open GL Includes
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>


#include "ShaderFactory.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <regex>

ShaderFactory::ShaderFactory()
{
	m_strShaderFolder = "Source/Shaders/Shaders/";
}

ShaderFactory::~ShaderFactory()
{
}

int ShaderFactory::ProcessShaders()
{
	m_ShaderProgram = glCreateProgram();

	std::vector<std::string> shaderFiles = RetrieveShaderFileNames();
	for (int i = 0; i < shaderFiles.size(); i++)
	{
		ProcessShader(m_strShaderFolder + shaderFiles[i]);
	}
	glLinkProgram(m_ShaderProgram);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	SaveCompiledShaderProgramToFile();
	return 0;
}

std::vector<std::string> ShaderFactory::RetrieveShaderFileNames()
{
	std::vector<std::string> output;

	WIN32_FIND_DATA data;
	HANDLE findHandle;
	const std::regex fileName("(\.frag|\.vs)");
	std::string searchPattern = "*";
	std::string filePath = m_strShaderFolder + searchPattern;

	findHandle = FindFirstFile(filePath.c_str(), &data);
	do
	{
		if (std::regex_search(data.cFileName, fileName))
		{
			output.push_back(data.cFileName);
		}
	} while (FindNextFile(findHandle, &data));

	return output;
}

void ShaderFactory::ProcessShader(std::string _fileName)
{
	GLuint compiledShader;
	std::string rawShader;
	try {
		rawShader = LoadShader(_fileName);
	}
	catch (std::exception& e) {
		//TODO:
		//Handle Exception
		return;
	}

	try {
		int extPos = _fileName.length() - 2;
		std::string extension = _fileName.substr(extPos);
		GLenum shaderType;
		if (extension == "vs")
		{
			shaderType = GL_VERTEX_SHADER;
		}
		else if (extension == "ag")
		{
			shaderType = GL_FRAGMENT_SHADER;
		}
		compiledShader = CompileShader(rawShader.c_str(), shaderType);
		glAttachShader(m_ShaderProgram, compiledShader);
	}
	catch (std::exception& e) {
		//TODO:
		//Handle Exception
		return;
	}

}

GLuint ShaderFactory::CompileShader(const GLchar * _shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &_shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

void ShaderFactory::SaveCompiledShaderProgramToFile()
{
	GLint length = 0;
	GLchar infoLog[512];

	glGetProgramiv(m_ShaderProgram, GL_PROGRAM_BINARY_LENGTH, &length);
	if (length < 1) {
		glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::Failed to Retrieve Shader Size\n" << infoLog << std::endl;
	}


	// Retrieve the binary code
	std::vector<GLubyte> buffer(length);
	GLenum format = 0;
	glGetProgramBinary(m_ShaderProgram, length, NULL, &format, buffer.data());

	std::ofstream shaderStream("AssetPack/shaderProgram.bin", std::ios::binary);

	shaderStream.write(reinterpret_cast<char*>(buffer.data()), length);
	shaderStream.close();
}

const std::string ShaderFactory::LoadShader(std::string _fileName)
{
	std::string filePath = _fileName;
	std::string rawInput;
	std::ifstream shaderIn;
	std::stringstream shaderStream;

	shaderIn.open(filePath);
	if (shaderIn.is_open() == true)
	{
		shaderStream = std::stringstream();
		shaderStream << shaderIn.rdbuf();
		shaderIn.close();
		rawInput = shaderStream.str();

		return rawInput;
	}
	else
	{
		std::cout << "Failed to load shader: " << _fileName << "\n";
		return nullptr;
	}
}
