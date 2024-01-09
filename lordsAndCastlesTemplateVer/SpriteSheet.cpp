#include "SpriteSheet.h"


SpriteSheet::SpriteSheet()
{
	m_spriteSheetRowArray = nullptr;
	m_surface = nullptr;
	m_sheet = nullptr;
	m_rows = 0;
	m_cols = 0;
}


SpriteSheet::SpriteSheet(Tmpl8::Surface* p_surface, Tmpl8::Surface* p_sheet, uint8_t p_rows, uint8_t p_cols)
{
	m_surface = p_surface;
	m_sheet = p_sheet;
	m_rows = p_rows;
	m_cols = p_cols;

	m_spriteSheetRowArray = new uint8_t[p_rows]();
}

int Clamp(int p_val, int p_min, int p_max)
{
	return p_val < p_min ? p_min : p_val > p_max ? p_max : p_val;
}

SpriteSheet::~SpriteSheet()
{
	if (m_sheet != nullptr)
	{
		delete m_sheet;
	}
}

void SpriteSheet::RenderFrom(int p_xPos, int p_yPos, int p_width, int p_height, uint8_t p_row, uint8_t p_col)
{
	Tmpl8::Pixel* usedSurf = m_sheet->GetBuffer();
	Tmpl8::Pixel* drawnSurf = m_surface->GetBuffer();

	//draw til from row x and col x
	float tileSizeX = m_sheet->GetWidth() / m_cols;
	float tileSizeY = m_sheet->GetHeight() / m_rows;

	float scaleX = tileSizeX / p_width;
	float scaleY = tileSizeY / p_height;

	// the whole sprite needs to be read but only p_width wide and p_height high
	for (int x = 0; x < p_width; x++)
	{
		int destX = x + p_xPos;

		if (destX > m_surface->GetWidth() - 1 || destX < 0)
		{
			continue;
		}

		for (int y = 0; y < p_height; y++)
		{
			int srcX = static_cast<int>(x * scaleX) + p_col * tileSizeX;
			int srcY = static_cast<int>(y * scaleY) + p_row * tileSizeY;
			int destY = y + p_yPos;

			if (destY > m_surface->GetHeight() - 1 || destY < 0)
			{
				continue;
			}

			if (srcX >= 0 && srcX < m_sheet->GetWidth() && srcY >= 0 && srcY < m_sheet->GetHeight())
			{
				Tmpl8::Pixel* newPixel = &usedSurf[srcX + srcY * m_sheet->GetPitch()];

				// Check for transparent pixels
				if ((*newPixel & 0x000000ff) > 1)
				{
					drawnSurf[destX + destY * m_surface->GetPitch()] = *newPixel;
				}
			}
		}
	}
}

int SpriteSheet::RowColCount(int p_index)
{
	return m_spriteSheetRowArray[p_index];
}

void SpriteSheet::SetCollumCountOfRow(uint8_t p_row, uint8_t p_count)
{
	if (p_row > m_rows)
	{
		printf("unable to set row, p_row index does not exsist \n");
		return;
	}

	m_spriteSheetRowArray[p_row] = p_count;
}