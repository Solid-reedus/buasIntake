#pragma once

#ifndef SPRITE_SHEET
#define SPRITE_SHEET

#include "surface.h"
#include <iostream>


	class SpriteSheet
	{
		public:
		SpriteSheet();
		SpriteSheet(Tmpl8::Surface* p_surface, Tmpl8::Surface* p_sheet, uint8_t p_rows, uint8_t p_cols);

		~SpriteSheet();
		void RenderFrom(int p_xPos, int p_yPos, int p_width, int p_height, uint8_t p_row, uint8_t p_col);
		// this is used for classes that use the spritesheet to easily check how many frames a row has
		int RowColCount(int p_index);
		void SetCollumCountOfRow(uint8_t p_row, uint8_t p_count);

		private:
		// m_surface is where too draw. m_sheet is where from to draw
		Tmpl8::Surface* m_surface, *m_sheet;
		uint8_t m_rows, m_cols;
		// heap mem of a array which the size is determined by p_rows in
		// the constructor
		uint8_t* m_spriteSheetRowArray;

		float m_tickTime = 0.0f, m_workingTimer = 0.0f;

	};

#endif