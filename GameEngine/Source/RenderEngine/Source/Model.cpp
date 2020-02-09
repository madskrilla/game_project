#include "stdafx.h"
#include "Model.h"


CModel::CModel()
{
}


CModel::~CModel()
{
}

void CModel::AddMesh(CMesh * mesh)
{
	m_vecMesh.push_back(mesh);
}
