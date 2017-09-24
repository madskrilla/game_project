#include "stdafx.h"
#include "RenderIncludes.h"

#include "Camera.h"

CCamera::CCamera()
{
	m_eType = CamType::PERSPECTIVE;

	if (m_eType == CamType::ORTHO)
	{
		m_matProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	}
	else
	{
		m_matProjection = glm::perspective(glm::radians(45.0f), float(800 / 600), 0.1f, 100.0f);
	}
	m_vecPosition = { 0.0f,0.0f,-3.0f };
	m_matView = glm::translate(m_matView, m_vecPosition);
}

CCamera::CCamera(CCamera & copy)
{

}

CCamera::~CCamera()
{

}

void CCamera::Update(float dt)
{
	
}

void CCamera::SendCameraToGPU(int & shaderProgram)
{
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_matProjection));

	unsigned int viewLocation = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_matView));
}

