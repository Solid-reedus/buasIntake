#ifndef MENU_SCENE
#define MENU_SCENE

#include "IScene.h"
#include "UIBaseHeader.h"


class MenuScene : public IScene
{
	public:

	MenuScene();
	MenuScene(SDL_Renderer* m_renderer, TTF_Font* m_font);
	~MenuScene();
	void Update() override;
	void GameLogic();
	bool Init(bool *m_quitGame, SDL_Renderer* m_renderer, TTF_Font* m_font);
	virtual void Clear() override;

	private:
	virtual void RenderScreen() override;
	SDL_Renderer* renderer;
	TTF_Font* font;
	Text testingText;
	bool *quitGame;


};

#endif