#include "stdafx.h"

#include "ModelManager.h"

#include "../../RenderEngine/Source/Model.h"
#include "../../RenderEngine/Source/Mesh.h"

CModelManager* CModelManager::m_pInst = nullptr;

CModelManager * CModelManager::GetInstance() {
	if (m_pInst == nullptr)
	{
		m_pInst = new CModelManager();
	}
	return m_pInst;
}

void CModelManager::Initialize() {
	CModel * model = LoadModel("Source/Assets/Models/nanosuit/nanosuit.obj");
	m_vecModel.push_back(model);
	int test = 0;
}

CModel * CModelManager::LoadModel(char * path)
{
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string error = importer.GetErrorString();
		return nullptr;
	}

	CModel * model = new CModel();
	ProcessNode(scene, scene->mRootNode, model);

	return model;
}

void CModelManager::ProcessNode(const aiScene * scene, aiNode * node, CModel * model) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		model->AddMesh(ProcessMesh(scene, mesh));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(scene, node->mChildren[i], model);
	}
}

CMesh* CModelManager::ProcessMesh(const aiScene * scene, aiMesh * mesh) {
	CMesh * myMesh = new CMesh();
	std::vector<Assimp_Vertex> verts;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Assimp_Vertex vert;
		vert.position = ProcessAssimpVec3(mesh->mVertices[i]);
		vert.normal = ProcessAssimpVec3(mesh->mNormals[i]);
		int channels = mesh->GetNumUVChannels();

		for (unsigned int u = 0; u < mesh->GetNumUVChannels(); u++)
		{
			vert.texCoords.push_back(ProcessAssimpVec3(*mesh->mTextureCoords[u]));
		}
		verts.push_back(vert);
	}

	//myMesh->BuildMesh(verts, NULL, NULL);
	return myMesh;
}

glm::vec3 CModelManager::ProcessAssimpVec3(aiVector3D pos) {
	glm::vec3 vect;

	vect.x = pos.x;
	vect.y = pos.y;
	vect.z = pos.z;

	return vect;
}

CModelManager::CModelManager()
{
}

CModelManager::CModelManager(CModelManager &)
{
}

CModelManager::~CModelManager()
{
}
