#include "stdafx.h"
#include <vld.h>

#include "RenderEngine/Source/RenderEngineInterface.h"
#include "PhysicsEngine\Source\PhysicsEngineInterface.h"
#include "AssetManager\Source\TextureManager.h"
#include "Game\Game.h"

CGame* game;
IRenderEngine* renderEngine;
IPhysicsEngine* physicsEngine;
CTextureManager * textureManager;

float deltaTime;

void InitializeModules();

/* 
	Main()
	Summary:
	Initialize Engine Modules
	Run Main Game Loop
	Destroy Modules on close
*/
int main()
{
	bool playing = true;
	game = CGame::GetInstance();
	renderEngine = IRenderEngine::GetInstance();
	physicsEngine = IPhysicsEngine::GetInstance();
	textureManager = CTextureManager::GetInstance();

	InitializeModules();

	while (playing)
	{
		deltaTime = renderEngine->DeltaTime();

		game->Update(deltaTime);
		physicsEngine->Update(deltaTime);
		playing = renderEngine->Update(deltaTime);
	}

	renderEngine->Destroy();
	physicsEngine->Destroy();
	textureManager->Destroy();
	game->Destroy();
}

void InitializeModules()
{
	renderEngine->Initialize();
	physicsEngine->Initialize();
	textureManager->Initialize();
	game->Initialize();
}