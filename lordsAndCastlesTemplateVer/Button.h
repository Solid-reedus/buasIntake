#pragma once

#include "Event.h"
#include "BaseHeader.h"
#include "surface.h"

class Button
{
	public:
	Button();
	Button(const Rect m_rect, const Tmpl8::Pixel m_btnColor, Tmpl8::Surface* m_surface);
	~Button();
	void SetText(char* m_text, Tmpl8::Pixel m_textColor = 0xffffff);
	void SetImage();
	void RenderBtn();
	void OnClick(const int m_x, const int m_y);
	Event event;


	private:
	Rect rect;
	//surface is from surface.h
	Tmpl8::Surface* surface;
	Tmpl8::Pixel btnColor;
	Tmpl8::Pixel textColor;
	char* text;

};
