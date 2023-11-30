#pragma once

#include "Event.h"
#include "BaseHeader.h"
#include "surface.h"

class Button
{
	public:
	Button();
	Button(const Rect p_rect, const Tmpl8::Pixel p_btnColor, Tmpl8::Surface* p_ptrSurface);
	~Button();
	void SetText(char* p_ptrText, Tmpl8::Pixel p_textColor = 0xffffff);
	void SetImage();
	void RenderBtn();
	void OnClick(const int p_x, const int p_y);
	Event event;


	private:
	Rect m_rect;
	//surface is from surface.h
	Tmpl8::Surface* m_ptrSurface;
	Tmpl8::Pixel m_btnColor;
	Tmpl8::Pixel m_textColor;
	char* m_ptrText;

};
