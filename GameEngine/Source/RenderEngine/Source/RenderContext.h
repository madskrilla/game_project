#pragma once

class CVertex;
class IRenderer;
class CTextureManager;
class CCamera;
class CGameObject;

class CRenderContext
{
public:
	CRenderContext();
	CRenderContext(CRenderContext&);

	~CRenderContext();

	//Methods
	void Initialize();
	void Render(float deltaTime);
	void Destroy();

	void AddRenderObject(IRenderer* render, unsigned int numVerts);
	void SetCamera(CCamera* cam);
private:
	//Shader Methods
	void InitializeVertexShader();
	void InitialzeFragmentShader();
	std::string LoadShader(std::string _fileName);
	void ComplileShader(const GLchar* _shaderSource, GLuint _shader);

	//Shader Program Methods
	void InitializeShaderProgram();

	void LinkShaderAttributes();

	void InitializeVertexBuffer();
	void UpdateVertexBuffer();

	void InitializeIndexBuffer();

	void RenderNode(IRenderer * node);

	CTextureManager* m_pTextureManager;
	CCamera* m_pCamera;

	//Shader File Names
	std::string m_strShaderFolder;
	std::string m_strVertexShader;
	std::string m_strFragmentShader;

	//Shaders
	GLuint m_sVertexShader;
	GLuint m_sFragmentShader;

	GLint m_ShaderProgram;

	//Buffers
	GLuint m_VertBufferObject;
	GLuint m_VertArrayObject;
	GLuint m_ElementArrayObjectIndicies;

	std::vector<VERT_POS_UV> m_vecVerticies;
	std::vector<unsigned int> m_vecIndicies;
	std::vector<IRenderer *> m_vecRenderers;
};
