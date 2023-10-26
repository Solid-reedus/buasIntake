#include "GameplayScene.h"
#include "BaseHeader.h"


GameplayScene::GameplayScene()
{
	renderer = nullptr;
	font = nullptr;
}


GameplayScene::GameplayScene(SDL_Renderer* m_renderer, TTF_Font* m_font)
{
	renderer = m_renderer;
	font = m_font;
}

GameplayScene::~GameplayScene()
{

}

void GameplayScene::GameLogic()
{

}


void GameplayScene::Update()
{

	bool quitGameplay = false;
	SDL_Event e;


	while (!quitGameplay)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quitGameplay = true;
				*quitGame = true;
				break;
			}
		}
		GameLogic();
		RenderScreen();
	}

	Clear();
}

bool GameplayScene::Init(bool *m_quitGame, SDL_Renderer* m_renderer, TTF_Font* m_font)
{
	quitGame = m_quitGame;
	renderer = m_renderer;
	font = m_font;

	Update();
	return true;
}

void GameplayScene::RenderScreen()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void GameplayScene::Clear()
{

}
