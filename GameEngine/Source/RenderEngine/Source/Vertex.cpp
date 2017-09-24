#include "stdafx.h"
#include "RenderIncludes.h"

#include "Vertex.h"

CVertex::CVertex()
{
}

CVertex::~CVertex()
{
}

bool CVertex::operator==(CVertex rght)
{
	GLfloat * rghtPosition = rght.GetPosition();
	GLfloat * rightUVs = rght.GetUV();

	for (unsigned int i = 0; i < 3; i++)
	{
		if (rghtPosition[i] != m_vecPosition[i])
		{
			return false;
		}

		if (i < 2 && rightUVs[i] != m_vecTexCoords[i])
		{
			return false;
		}
	}

	return true;
}

void CVertex::SetPosition(GLfloat position[])
{
	for (unsigned int i = 0; i < 3; i++)
	{
		m_vecPosition[i] = position[i];
	}
}

void CVertex::SetPosition(float x, float y, float z)
{
	m_vecPosition[0] = x;
	m_vecPosition[1] = y;
	m_vecPosition[2] = z;
}

void CVertex::SetTexCoords(GLfloat texCoords[])
{
	for (unsigned int i = 0; i < 2; i++)
	{
		m_vecTexCoords[i] = texCoords[i];
	}
}
void CVertex::SetTexCoords(float u, float v)
{
	m_vecTexCoords[0] = u;
	m_vecTexCoords[1] = v;
}