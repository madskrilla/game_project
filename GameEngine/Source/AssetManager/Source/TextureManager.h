#pragma once
#include <map>

class CTextureManager
{
private:
	//Name of the file containing a list of textures used in game
	const std::string m_strTextureManifestName = "TextureManifest.txt";

	//Hidden for Singleton
	CTextureManager();
	CTextureManager(CTextureManager &);
	~CTextureManager();

public:
	//Instance Accessor
	static CTextureManager * GetInstance();

	//Public API
	void Initialize();
	void Destroy();
	unsigned int GetTexture(std::string name);

private:

	//Members
	static CTextureManager * m_pInst;
	std::map<std::string, unsigned int> m_mapTextures;
	std::string m_strTextureFolder;

	//Methods
	void LoadTextures();
};