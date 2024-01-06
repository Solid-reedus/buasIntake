#include "Tile.h"

Tile::Tile()
{
	m_spriteSheet = nullptr;
	tileFlags = tlfNone;

	m_row = 0;
	m_col = 0;

}

Tile::Tile(SpriteSheet* p_spriteSheet, uint8_t p_row, uint8_t p_col, 
	TileFlags p_tileFlags)
{
	m_spriteSheet = p_spriteSheet;
	tileFlags = p_tileFlags;

	m_row = p_row;
	m_col = p_col;

}

Tile::~Tile()
{
	m_spriteSheet = nullptr;
}

void Tile::Render(int p_xPos, int p_yPos, int p_width, int p_height)
{
	m_spriteSheet->RenderFrom(p_xPos, p_yPos, p_width, p_height, m_row, m_col);
}
