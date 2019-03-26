#include "stdafx.h"
#include "RenderIncludes.h"

#include "Camera.h"

CCamera::CCamera()
{
	m_eType = CamType::PERSPECTIVE;

	if (m_eType == CamType::ORTHO)
	{
		m_matProjection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.1f, 100.0f);
	}
	else
	{
		m_matProjection = glm::perspective(glm::radians(45.0f), float(1920 / 1080), 0.1f, 100.0f);
	}
	m_vecPosition = { 0.0f,0.0f,-10.0f };
	m_matView = glm::translate(m_matView, m_vecPosition);
}

CCamera::CCamera(CCamera & copy)
{

}

CCamera::~CCamera()
{

}

void CCamera::Initialize(int & shaderProgram)
{
	m_nProjectionLocation = glGetUniformLocation(shaderProgram, "projection");
	m_nViewLocation = glGetUniformLocation(shaderProgram, "view");
}

void CCamera::Update(float dt)
{
	
}

void CCamera::SendCameraToGPU()
{
	glUniformMatrix4fv(m_nProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_matProjection));
	glUniformMatrix4fv(m_nViewLocation, 1, GL_FALSE, glm::value_ptr(m_matView));
}

