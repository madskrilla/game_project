#pragma once
#include <map>

class CTextureManager
{
private:
	struct Texture
	{
		int width, height, numChannels;
		std::string name;
	};

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