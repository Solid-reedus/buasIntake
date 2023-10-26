#include "MenuScene.h"
#include "BaseHeader.h"

MenuScene::MenuScene()
{
	renderer = nullptr;
	font = nullptr;
}


MenuScene::MenuScene(SDL_Renderer* m_renderer, TTF_Font* m_font)
{
	renderer = m_renderer;
	font = m_font;
	testingText;
}

MenuScene::~MenuScene()
{

}

void MenuScene::GameLogic()
{

}

void MenuScene::Update()
{

	bool quitMenu = false;
	SDL_Event e;


	while (!quitMenu)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quitMenu = true;
				*quitGame = true;
				break;
			}
		}
		GameLogic();
		RenderScreen();
	}

	Clear();
}

bool MenuScene::Init(bool *m_quitGame, SDL_Renderer* m_renderer, TTF_Font* m_font)
{
	quitGame = m_quitGame;
	renderer = m_renderer;
	font = m_font;


	testingText = Text("testing text", 50, 150, 50, font, {250, 10, 10}, renderer, left);


	Update();

	return true;
}

void MenuScene::RenderScreen() 
{
	SDL_RenderClear(renderer);

	testingText.Render();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void MenuScene::Clear() 
{
	renderer = nullptr;
	font = nullptr;
	quitGame = nullptr;
}
