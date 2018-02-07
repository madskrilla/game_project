/*
	RenderContext.cpp

	Purpose:
	Holds a shader program and all of the render objects it is responsible for

	Last Modified:
	2/6/2018
	Reason:
	Adding Comments
*/
#include "stdafx.h"
#include "RenderIncludes.h"

#include "RenderContext.h"
#include "IRenderer.h"
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

/*
	Initialize()
	Summary:
	Gets necessary references to outside modules
	Initializes shaders and buffers
*/
void CRenderContext::Initialize()
{
	m_pTextureManager = CTextureManager::GetInstance();

	InitializeVertexShader();
	InitialzeFragmentShader();

	InitializeShaderProgram();

	InitializeVertexBuffer();
	InitializeIndexBuffer();
}

/*
	InitializeVertexShader()
	Summary:
	Loads and compiles the vertex shader
*/
void CRenderContext::InitializeVertexShader()
{
	m_sVertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string shader = LoadShader(m_strVertexShader);
	const GLchar * source = shader.c_str();

	ComplileShader(source, m_sVertexShader);
}

/*
	InitializeFragmentShader()
	Summary:
	Loads and compiles the fragment shader
*/
void CRenderContext::InitialzeFragmentShader()
{
	m_sFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string shader = LoadShader(m_strFragmentShader);
	const GLchar * source = shader.c_str();

	ComplileShader(source, m_sFragmentShader);
}

/*
	LoadShader( string Filename )
	Params:
	filename - name of the shaderfile to be loaded

	Summary:
	Takes in a filename
	Finds the given shader
	Returns the raw text in the file
*/
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

/*
	CompileShader( const GLchar* shaderSource, GLuint shader )
	Params:
	shaderSource - raw text of a shader program
	shader - variable to store shader pointer

	Summary:
	Compiles shader source code
	Stores compiled shader
*/
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

/*
	InitializeShaderProgram()
	Summary:
	Creates a new shader program
	Attaches associated shaders to the program
*/
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

/*
	LinkShaderAttributes()
	Summary:
	Establishes the memory location of vertex attributes
*/
void CRenderContext::LinkShaderAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERT_POS_UV), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VERT_POS_UV), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

/*
	InitializeVertexBuffer()
	Summary:
	Allocates the buffer to hold all the verticies in the renderset
	Link vertex attributes to the shader program
*/
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

/* 
	UpdateVertexBuffer()
	Summary:
	Attach the vertex list to the vertex buffer
*/
void CRenderContext::UpdateVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertBufferObject);
	glBindVertexArray(m_VertArrayObject);

	glBufferData(GL_ARRAY_BUFFER, m_vecVerticies.size() * sizeof(VERT_POS_UV), &m_vecVerticies[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*
	InitializeIndexBuffer()
	Summary:
	Attach the list of indicies to the index buffer
*/
void CRenderContext::InitializeIndexBuffer()
{
	glGenBuffers(1, &m_ElementArrayObjectIndicies);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementArrayObjectIndicies);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*
	RenderNode( IRenderer* Node )
	Params:
	Node - the object to be rendered

	Summary:
	Gets the number of and starting index
	Sets the nodes texture and transform matrix in the shader
	Draws the object
*/
void CRenderContext::RenderNode(IRenderer * node)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementArrayObjectIndicies);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, node->GetNumIndicies() * sizeof(unsigned int), &m_vecIndicies[node->GetStartIndex()], GL_STATIC_DRAW);
	glBindTexture(GL_TEXTURE_2D, node->GetTexture());

	unsigned int transformLoc = glGetUniformLocation(m_ShaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(node->GetTransformMatrix()));

	glDrawElements(GL_TRIANGLES, (int)node->GetNumIndicies(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*
	AddRenderObject( IRenderer* Render, unsigned int NumVerts )
	Params:
	Render - the renderer for the new object
	NumVerts - the number of verticies contained in the object

	Summary:
	Determines if a vertex exists in the vertex buffer
	If vertex exists, add its index to the index buffer
	else add the vertex to the vertex buffer, its index is the current size of the buffer
*/
void CRenderContext::AddRenderObject(IRenderer* render, unsigned int numVerts)
{
	render->SetIndexStart((unsigned int)m_vecIndicies.size());
	VERT_POS_UV* verts = (VERT_POS_UV*)render->GetVertexArray();
	bool vertExists = false;

	for (unsigned int i = 0; i < 6; i++)
	{
		vertExists = false;
		for (unsigned int j = 0; j < m_vecVerticies.size(); j++)
		{
			if (m_vecVerticies[j] == verts[i])
			{
				m_vecIndicies.push_back(j);
				vertExists = true;
			}
		}
		if (vertExists == false)
		{
			m_vecVerticies.push_back(verts[i]);
			m_vecIndicies.push_back((int)m_vecVerticies.size() - 1);
		}
	}
	render->SetTexture(m_pTextureManager->GetTexture(render->GetTextureName()));

	m_vecRenderers.push_back(render);
	UpdateVertexBuffer();
}

/*
	Render()
	Summary:
	Set shader program
	Set Vertex array
	Render Objects
*/
void CRenderContext::Render()
{
	glUseProgram(m_ShaderProgram);

	glBindVertexArray(m_VertArrayObject);
	m_pCamera->SendCameraToGPU(m_ShaderProgram);

	for (unsigned int i = 0; i < m_vecRenderers.size(); i++)
	{
		RenderNode(m_vecRenderers[i]);
	}
}

/*
	Destroy()
	Summary:
	Deallocate any memory allocated in the RenderContext
*/
void CRenderContext::Destroy()
{
	delete m_pCamera;

	m_vecVerticies.clear();
	m_vecRenderers.clear();
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