#include "game.h"


namespace Tmpl8
{
	void Game::Init()
	{
		m_ptrCurrentScene = std::make_unique<MenuScene>(m_ptrScreen, (Tmpl8::Game*)this);
		m_ptrCurrentScene->InitScene();
	}



	void Game::Shutdown()
	{

	}

	void Game::KeyDown(int key)
	{
		// notify currentScene that key is pressed
	}


	void Game::MouseDown(int button, int x, int y)
	{
		m_ptrCurrentScene->MouseDown(button, x, y);
		//printf("buttom: %d  where: x=%d y=%d \n", button, x, y);
	}

	void Game::Tick(float deltaTime)
	{
		m_ptrScreen->Clear(0);
		m_ptrCurrentScene->Update();
	}

	void Game::ChangeScene(GameScene newScene)
	{
		switch (newScene)
		{
				
			break;
			case menuScn:
			break;
			case gameplayScn:
			break;
			case noneScn:
			default:
			break;
		}
		printf("ChangeScene \n");

	}
};