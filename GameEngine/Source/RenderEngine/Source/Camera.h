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

	void Initialize(int & shaderProgram);
	void Update(float deltaTime);
	void SendCameraToGPU();

private:

	glm::vec3 m_vecPosition;
	glm::vec3 m_vecRotation;

	glm::mat4 m_matProjection;
	glm::mat4 m_matView;

	unsigned int m_nViewLocation;
	unsigned int m_nProjectionLocation;

	CamType m_eType;
};