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
		if (m_ptrCurrentScene != nullptr)
		{
			m_ptrCurrentScene->Delete();
		}
	}

	void Game::KeyDown(SDL_Keycode key)
	{
		m_ptrCurrentScene->KeyDown(key);
	}

	void Game::MouseDown(int button, int x, int y)
	{
		m_ptrCurrentScene->MouseDown(button, x, y);
	}

	void Game::MouseMove(int x, int y)
	{
		m_ptrCurrentScene->MouseMove(x, y);
	}

	void Game::MouseScroll(int y)
	{
		m_ptrCurrentScene->MouseScroll(y);
	}

	void Game::Tick(float deltaTime)
	{
		m_ptrScreen->Clear(0);
		m_ptrCurrentScene->Update(deltaTime);
	}

	void Game::ChangeScene(GameSceneEnum newScene)
	{
		m_ptrCurrentScene->Delete();
		switch (newScene)
		{
			break;
			case menuScn:
				printf("changed scene to menu \n");
				m_ptrCurrentScene = std::move(std::make_unique<MenuScene>(m_ptrScreen, (Tmpl8::Game*)this));
				break;
			case gameplayScn:
				printf("changed scene to game \n");
				m_ptrCurrentScene = std::move(std::make_unique<GameScene>(m_ptrScreen, (Tmpl8::Game*)this));
				break;
			case howToPlayScn:
				printf("changed scene to how to play \n");
				m_ptrCurrentScene = std::move(std::make_unique<HowToPlayScene>(m_ptrScreen, (Tmpl8::Game*)this));
				break;
			break;
			case noneScn:
			default:
			break;
		}

		m_ptrCurrentScene->InitScene();
	}
};