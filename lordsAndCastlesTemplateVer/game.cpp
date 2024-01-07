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