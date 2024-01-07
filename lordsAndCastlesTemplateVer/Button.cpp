#include "Button.h"


Button::Button()
{
	m_rect = { 0,0,0,0 };
	m_btnColor = 0;
	m_textColor = 0;
	m_textScale = 0;

	m_ptrSurface = nullptr;
	m_ptrText = nullptr;
}

Button::Button(const RectInt p_rect, const Tmpl8::Pixel p_btnColor, Tmpl8::Surface* p_ptrSurface)
{
	m_rect = p_rect;
	m_btnColor = p_btnColor;
	m_textColor = 0x000000;
	m_ptrSurface = p_ptrSurface;
	m_ptrText = nullptr;
	m_textScale = 0;
}

Button::Button(const RectInt p_rect, const Tmpl8::Pixel p_btnColor, Tmpl8::Surface* p_ptrSurface, 
	char* p_text, uint8_t p_scale, Tmpl8::Pixel p_textColor)
{
	m_rect = p_rect;
	m_btnColor = p_btnColor;
	m_textColor = p_textColor;
	m_ptrSurface = p_ptrSurface;
	m_ptrText = p_text;
	m_textScale = p_scale;
}

void Button::SetText(char* p_text, uint8_t p_scale, Tmpl8::Pixel p_textColor)
{
	m_textScale = p_scale;
	m_textColor = p_textColor;
	m_textColor = p_textColor;
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
		// each letter is 5 pixels in height and width
		int offset = (strlen(m_ptrText) * m_textScale * 5) / 2;
		m_ptrSurface->PrintScaled(m_ptrText, m_rect.x + (m_rect.w / 2) - offset - strlen(m_ptrText), m_rect.y + (m_rect.h / 2) - m_textScale, m_textColor, static_cast<int>(m_textScale));
	}
}

Button::~Button()
{

}

void Button::OnClick(const int p_x, const int p_y)
{
	// if click pos is within the bounds of the rect
	// then invoke every event tied to this instance of the button
	if (m_rect.IsInside(p_x, p_y))
	{
		event.Invoke();
	}
}