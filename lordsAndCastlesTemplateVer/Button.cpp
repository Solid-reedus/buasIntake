#include "Button.h"


Button::Button()
{
	rect = { 0,0,0,0 };
	btnColor = 0;
	textColor = 0;

	surface = nullptr;
	text = nullptr;
}

Button::Button(const Rect m_rect, const Tmpl8::Pixel m_btnColor, Tmpl8::Surface* m_surface)
{
	rect = m_rect;
	btnColor = m_btnColor;
	textColor = 0x000000;
	surface = m_surface;
	text = nullptr;
}

void Button::RenderBtn()
{
	if (surface == nullptr)
	{
		printf("button unasigned surface \n");
		return;
	}

	surface->Bar(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, btnColor);
	if (text != nullptr)
	{
		surface->Print(text, rect.x + 10, rect.y + 10, textColor);
	}
}

Button::~Button()
{

}


void Button::OnClick(const int m_x, const int m_y)
{
	// if click pos is within the bounds of the rect
	// then invoke every event tied to this instance of the button
	if (m_x > rect.x && m_x < rect.x + rect.w &&
		m_y > rect.y && m_y < rect.y + rect.h)
	{
		event.Invoke();
	}
}