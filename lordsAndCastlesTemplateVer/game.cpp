#include "game.h"
#include "surface.h"
#include "BaseScene.h"
#include "BaseHeader.h"
#include "Scenes.h"

std::unique_ptr<BaseScene> currentScene = nullptr;

namespace Tmpl8
{
	void Game::Init()
	{
		// init first scene
		currentScene = std::make_unique<MenuScene>(screen);
	}
	
	void Game::Shutdown()
	{

	}

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		currentScene->Update();
	}
};