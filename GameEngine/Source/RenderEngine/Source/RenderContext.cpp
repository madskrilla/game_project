#include "stdafx.h"
#include "RenderIncludes.h"

#include "RenderContext.h"
#include "Vertex.h"
#include "RenderNode.h"
#include "Camera.h"
#include "../../AssetManager/Source/TextureManager.h"
#include "../../Game/GameObject.h"

#include <iostream>
#include <fstream>
#include <sstream>

CRenderContext::CRenderContext()
{
	m_strShaderFolder = "Source/RenderEngine/Source/Shaders/";
	m_strVertexShader = "VS_POS_TEX.vs";
	m_strFragmentShader = "FS_POS_TEX.frag";
}

CRenderContext::CRenderContext(CRenderContext& _other)
{
}

CRenderContext::~CRenderContext()
{
}

void CRenderContext::Initialize()
{
	m_pTextureManager = CTextureManager::GetInstance();

	InitializeVertexShader();
	InitialzeFragmentShader();

	InitializeShaderProgram();

	InitializeVertexBuffer();
	InitializeIndexBuffer();
}

void CRenderContext::InitializeVertexShader()
{
	m_sVertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string shader = LoadShader(m_strVertexShader);
	const GLchar * source = shader.c_str();

	ComplileShader(source, m_sVertexShader);
}

void CRenderContext::InitialzeFragmentShader()
{
	m_sFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string shader = LoadShader(m_strFragmentShader);
	const GLchar * source = shader.c_str();

	ComplileShader(source, m_sFragmentShader);
}

std::string CRenderContext::LoadShader(std::string _fileName)
{
	std::string filePath = m_strShaderFolder + _fileName;
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

void CRenderContext::ComplileShader(const GLchar* _shaderSource, GLuint _shader)
{
	glShaderSource(_shader, 1, &_shaderSource, NULL);
	glCompileShader(_shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void CRenderContext::InitializeShaderProgram()
{
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_sVertexShader);
	glAttachShader(m_ShaderProgram, m_sFragmentShader);

	glLinkProgram(m_ShaderProgram);

	// check for linking errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void CRenderContext::LinkShaderAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void CRenderContext::InitializeVertexBuffer()
{
	glGenVertexArrays(1, &m_VertArrayObject);
	glBindVertexArray(m_VertArrayObject);

	glGenBuffers(1, &m_VertBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertBufferObject);

	LinkShaderAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CRenderContext::UpdateVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertBufferObject);
	glBindVertexArray(m_VertArrayObject);

	glBufferData(GL_ARRAY_BUFFER, m_vecVerticies.size() * sizeof(CVertex), &m_vecVerticies[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CRenderContext::InitializeIndexBuffer()
{
	glGenBuffers(1, &m_ElementArrayObjectIndicies);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementArrayObjectIndicies);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CRenderContext::RenderNode(CRenderNode * node)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementArrayObjectIndicies);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, node->GetIndexArray().size() * sizeof(int), &node->GetIndexArray()[0], GL_STATIC_DRAW);
	glBindTexture(GL_TEXTURE_2D, node->GetTexture());

	unsigned int transformLoc = glGetUniformLocation(m_ShaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(node->GetTransform()));

	glDrawElements(GL_TRIANGLES, (int)node->GetIndexArray().size(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CRenderContext::CreateRenderNode(std::vector<CVertex*> verts, CGameObject* obj)
{
	CRenderNode* node = new CRenderNode();

	bool vertExists;
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		vertExists = false;
		for (unsigned int j = 0; j < m_vecVerticies.size(); j++)
		{
			if (m_vecVerticies[j] == *verts[i])
			{
				node->AddIndex(j);
				m_vecIndicies.push_back(j);
				vertExists = true;
				break;
			}
		}
		if (vertExists == false)
		{
			m_vecVerticies.push_back(*verts[i]);
			node->AddIndex((int)m_vecVerticies.size() - 1);
			m_vecIndicies.push_back((int)m_vecVerticies.size() - 1);
		}
	}

	node->SetTexture(m_pTextureManager->GetTexture(obj->GetTexture()));
	obj->SetRenderNode(node);

	m_vecRenderNodes.push_back(node);
	UpdateVertexBuffer();
}

void CRenderContext::Render(float deltaTime)
{
	glUseProgram(m_ShaderProgram);

	glBindVertexArray(m_VertArrayObject);
	m_pCamera->SendCameraToGPU(m_ShaderProgram);

	for (unsigned int i = 0; i < m_vecRenderNodes.size(); i++)
	{
		RenderNode(m_vecRenderNodes[i]);
	}
}

void CRenderContext::Destroy()
{
	m_vecVerticies.clear();
	m_vecRenderNodes.clear();
	m_vecIndicies.clear();

	GLuint buffers[] = { m_VertBufferObject, m_ElementArrayObjectIndicies };

	glDeleteVertexArrays(1, &m_VertArrayObject);
	glDeleteBuffers(2, buffers);

	glDeleteShader(m_sVertexShader);
	glDeleteShader(m_sFragmentShader);
}

void CRenderContext::SetCamera(CCamera* cam)
{
	m_pCamera = cam;
}