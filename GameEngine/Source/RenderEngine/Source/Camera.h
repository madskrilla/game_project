#pragma once

enum CamType
{
	ORTHO = 0,
	PERSPECTIVE
};

class CCamera
{
public:

	CCamera();
	CCamera(CCamera &);

	~CCamera();

	void Update(float deltaTime);
	void SendCameraToGPU(int & shaderProgram);

private:

	glm::vec3 m_vecPosition;
	glm::vec3 m_vecRotation;

	glm::mat4 m_matProjection;
	glm::mat4 m_matView;

	CamType m_eType;
};