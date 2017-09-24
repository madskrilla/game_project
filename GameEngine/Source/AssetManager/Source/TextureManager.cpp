#include "stdafx.h"
#include "TextureManager.h"
#include "../../RenderEngine/Source/RenderIncludes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>

CTextureManager* CTextureManager::m_pInst = nullptr;

CTextureManager::CTextureManager()
{
}
CTextureManager::CTextureManager(CTextureManager &)
{
}
CTextureManager::~CTextureManager()
{
}

CTextureManager* CTextureManager::GetInstance()
{
	if (m_pInst == nullptr)
	{
		m_pInst = new CTextureManager();
	}
	return m_pInst;
}

void CTextureManager::Initialize()
{
	m_strTextureFolder = "Source/Assets/Textures/";
	LoadTextures();
}

void CTextureManager::LoadTextures()
{
	std::vector<Texture*> vecTextures;

	WIN32_FIND_DATA data;
	HANDLE findHandle;
	std::string searchPattern = "*.jpg";
	std::string filePath = m_strTextureFolder + searchPattern;

	findHandle = FindFirstFile(filePath.c_str(), &data);
	do
	{
		Texture * newText = new Texture();
		newText->name = data.cFileName;
		vecTextures.push_back(newText);
	} while (FindNextFile(findHandle, &data));

	for (unsigned int i = 0; i < vecTextures.size(); i++)
	{
		Texture * tex = vecTextures[i];
		std::string file = m_strTextureFolder + tex->name;
		unsigned char * data = stbi_load(file.c_str(), &(tex->width), &(tex->height), &(tex->numChannels), 0);

		GLuint texture = 0;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		m_mapTextures.insert(std::pair<std::string, unsigned int>(tex->name, texture));
		stbi_image_free(data);
	}

	vecTextures.clear();
}

unsigned int CTextureManager::GetTexture(std::string name)
{
	return m_mapTextures[name];
}