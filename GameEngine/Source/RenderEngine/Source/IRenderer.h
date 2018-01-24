#pragma once

#include "RenderIncludes.h"

class IRenderer
{
public:
	IRenderer() {};
	IRenderer(IRenderer& copy) {};
	~IRenderer() {};

	virtual void Initialize() {};
	virtual void* GetVertexArray() = 0;
	virtual void UpdateTransform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale) {};

	//Mutators
	void SetTexture(GLuint text)						{ m_nTexture = text; }
	void SetIndexStart(unsigned int start)				{ m_nIndexStart = start; }
	void SetNumIndicies(unsigned int numIndicies)		{ m_nNumIndicies = numIndicies; }
	void SetTextureName(std::string name)				{ m_strTextureName = name; }

	//Accessors
	const GLuint GetTexture()						{ return m_nTexture; }
	const glm::mat4 GetTransformMatrix()			{ return m_matTransform; };
	const unsigned int GetStartIndex()				{ return m_nIndexStart; }
	virtual const unsigned int GetNumIndicies()		{ return -1; }
	const std::string GetTextureName()				{ return m_strTextureName; }

protected:

	GLuint m_nTexture;
	std::string m_strTextureName;
	glm::mat4 m_matTransform;
	unsigned int m_nIndexStart, m_nNumIndicies;
};