#pragma once

#include "Event.h"
#include "BaseHeader.h"
#include "surface.h"
#include "Rect.h"



class Button
{
	public:
	Button();
	Button(const RectInt p_rect, const Tmpl8::Pixel p_btnColor, Tmpl8::Surface* p_ptrSurface);
	Button(const RectInt p_rect, const Tmpl8::Pixel p_btnColor, Tmpl8::Surface* p_ptrSurface, 
		char* p_text, uint8_t p_scale, Tmpl8::Pixel p_textColor = 0xffffff);
	~Button();
	void SetText(char* p_text, uint8_t p_scale, Tmpl8::Pixel p_textColor = 0xffffff);
	void RenderBtn();
	void OnClick(const int p_x, const int p_y);
	Event event;


	private:
	RectInt m_rect;
	//surface is from surface.h
	Tmpl8::Surface* m_ptrSurface;
	Tmpl8::Pixel m_btnColor;
	Tmpl8::Pixel m_textColor;
	uint8_t m_textScale;
	char* m_ptrText;

};
