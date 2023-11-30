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
	}

	void Game::Tick(float deltaTime)
	{
		m_ptrScreen->Clear(0);
		m_ptrCurrentScene->Update();
	}

	void Game::ChangeScene(GameSceneEnum newScene)
	{
		switch (newScene)
		{
			break;
			case menuScn:
				m_ptrCurrentScene = std::move(std::make_unique<MenuScene>(m_ptrScreen, (Tmpl8::Game*)this));
				break;
			case gameplayScn:
				m_ptrCurrentScene = std::move(std::make_unique<GameScene>(m_ptrScreen, (Tmpl8::Game*)this));
			break;
			case noneScn:
			default:
			break;
		}
	}
};