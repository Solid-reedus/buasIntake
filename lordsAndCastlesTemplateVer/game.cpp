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

	void Game::KeyDown(SDL_Keycode key)
	{
		// notify currentScene that key is pressed
		m_ptrCurrentScene->KeyDown(key);
	}

	void Game::MouseDown(int button, int x, int y)
	{
		m_ptrCurrentScene->MouseDown(button, x, y);
	}

	void Game::MouseUp(int button, int x, int y)
	{

	}

	void Game::MouseMove(int x, int y)
	{
		m_ptrCurrentScene->MouseMove(x, y);
	}

	void Game::MouseScroll(int y)
	{
		m_ptrCurrentScene->MouseScroll(y);
	}

	void Game::KeyUp(SDL_Keycode  key)
	{
		//void KeyUp(SDL_Keycode  key)
	}




	void Game::Tick(float deltaTime)
	{
		m_ptrScreen->Clear(0);
		m_ptrCurrentScene->Update(deltaTime);
	}

	void Game::ChangeScene(GameSceneEnum newScene)
	{
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