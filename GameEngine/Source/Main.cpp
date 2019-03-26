#include "stdafx.h"

#if _DEBUG
	#include <vld.h>
#endif

#include "RenderEngine/Source/RenderEngineInterface.h"
#include "PhysicsEngine\Source\PhysicsEngineInterface.h"
#include "AssetManager\Source\TextureManager.h"
#include "Game\Game.h"

CGame* game;
IRenderEngine* renderEngine;
IPhysicsEngine* physicsEngine;
CTextureManager * textureManager;

double deltaTime;

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
		deltaTime = renderEngine->GetDeltaTime();

		game->Update(deltaTime);
		physicsEngine->Update(deltaTime);
		playing = renderEngine->Update();
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