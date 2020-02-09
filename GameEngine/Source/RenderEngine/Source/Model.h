#pragma once

class CMesh;

class CModel
{
public:
	CModel();
	~CModel();

	void AddMesh(CMesh * mesh);
private:

	std::vector<CMesh*> m_vecMesh;
};

