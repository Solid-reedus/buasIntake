#ifndef BASE_HEADER
#include "BaseHeader.h"
#endif

#ifndef UI_BASE_HEADER
#include "UIBaseHeader.h"
#endif

#ifndef SPRITE
#define SPRITE

class Sprite
{
	public:
	Sprite();
	Sprite(SDL_Renderer* m_renderer, TTF_Font* m_font, SDL_Texture* m_spriteSheet = nullptr);
	void SetSpriteSheet(SDL_Texture* m_spriteSheet);
	void RenderFrame();

	~Sprite();

	private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* spriteSheet;

	uint8_t currentFrame, currentAnim;

};

#endif
