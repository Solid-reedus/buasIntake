#include "Button.h"


Button::Button()
{
	m_rect = { 0,0,0,0 };
	m_btnColor = 0;
	m_textColor = 0;

	m_ptrSurface = nullptr;
	m_ptrText = nullptr;
}

Button::Button(const Rect p_rect, const Tmpl8::Pixel p_btnColor, Tmpl8::Surface* p_ptrSurface)
{
	m_rect = p_rect;
	m_btnColor = p_btnColor;
	m_textColor = 0x000000;
	m_ptrSurface = p_ptrSurface;
	m_ptrText = nullptr;
}

void Button::RenderBtn()
{
	if (m_ptrSurface == nullptr)
	{
		printf("button unasigned surface \n");
		return;
	}

	m_ptrSurface->Bar(m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y + m_rect.h, m_btnColor);
	if (m_ptrText != nullptr)
	{
		m_ptrSurface->Print(m_ptrText, m_rect.x + 10, m_rect.y + 10, m_textColor);
	}
}

Button::~Button()
{

}

void Button::OnClick(const int p_x, const int p_y)
{
	// if click pos is within the bounds of the rect
	// then invoke every event tied to this instance of the button
	if (p_x > m_rect.x && p_x < m_rect.x + m_rect.w &&
		p_y > m_rect.y && p_y < m_rect.y + m_rect.h)
	{
		event.Invoke();
	}
}