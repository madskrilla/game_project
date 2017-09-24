#pragma once

class CVertex
{
private:

	GLfloat m_vecPosition[3];
	GLfloat m_vecTexCoords[2];

public:
	CVertex();
	~CVertex();
	bool operator==(CVertex rght);

	GLfloat* GetPosition() { return m_vecPosition; }
	GLfloat* GetUV() { return m_vecTexCoords; }

	void SetPosition(GLfloat position[]);
	void SetPosition(float x, float y, float z);

	void SetTexCoords(GLfloat texCoords[]);
	void SetTexCoords(float u, float v);
};