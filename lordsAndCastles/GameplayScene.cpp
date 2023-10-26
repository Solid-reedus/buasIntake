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

	printf("menu scene\n");
}

GameplayScene::~GameplayScene()
{

}

void GameplayScene::Update()
{


	RenderScreen();
}

bool GameplayScene::Init(bool *m_quitGame, SDL_Renderer* m_renderer, TTF_Font* m_font)
{
	quitGame = m_quitGame;
	renderer = m_renderer;
	font = m_font;

	return true;
}

void GameplayScene::RenderScreen()
{
	printf("menu \n");

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void GameplayScene::Clear()
{

}
