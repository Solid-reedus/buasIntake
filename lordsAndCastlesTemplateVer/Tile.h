#pragma once

#include "SpriteSheet.h"

enum TileFlags
{
	tlfNone		 = 0,
	tlfwalkable  = 1,
	tlfplaceable = 2,
};

class Tile
{
	public:
	Tile();
	Tile(SpriteSheet* p_spriteSheet, uint8_t p_row, uint8_t p_col, TileFlags p_tileFlags);

	~Tile();
	void Render(int p_xPos, int p_yPos, int p_width, int p_height);

	TileFlags tileFlags;

	private:
	uint8_t m_row, m_col;
	SpriteSheet* m_spriteSheet;
};

