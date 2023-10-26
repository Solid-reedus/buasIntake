#ifndef GAMEPLAY_SCENE
#define GAMEPLAY_SCENE

#include "IScene.h"
#include "UIBaseHeader.h"

class GameplayScene : public IScene
{
	public:
	GameplayScene();
	GameplayScene(SDL_Renderer* m_renderer, TTF_Font* m_font);
	~GameplayScene();
	void Update() override;
	bool Init(bool *m_quitGame, SDL_Renderer* m_renderer, TTF_Font* m_font);
	virtual void Clear() override;
	
	private:
	virtual void RenderScreen() override;
	SDL_Renderer* renderer;
	TTF_Font* font;
	bool *quitGame;

};

#endif