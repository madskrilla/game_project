#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "RenderEngine/Source/RenderIncludes.h"

class CModel;
class CMesh;

class CModelManager {
public :
	static CModelManager* GetInstance();
	void Initialize();

	CModel* LoadModel(char * path);
private:
	CModelManager();
	CModelManager(CModelManager &);
	~CModelManager();

	void ProcessNode(const aiScene * scene, aiNode * node, CModel * model);
	CMesh * ProcessMesh(const aiScene * scene, aiMesh * mesh);
	glm::vec3 ProcessAssimpVec3(aiVector3D pos);

	std::vector<CModel*> m_vecModel;

	static CModelManager* m_pInst;
};