#ifndef BASE_HEADER
#include "BaseHeader.h"
#endif

#ifndef UI_BASE_HEADER
#include "UIBaseHeader.h"
#endif

#ifndef TILE
#define TILE

class Tile
{
	public:
	Tile();
	Tile(SDL_Renderer* m_renderer, TTF_Font* m_font, SDL_Texture* m_texture = nullptr);
	void LoadTexture(SDL_Texture* m_texture);
	void Render();
	~Tile();

	private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* texture;

};

#endif
