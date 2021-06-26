#include "Text.h"

void Text::Draw(Graphics* g)
{
	std::string _font = GetFont();
	std::wstring font = std::wstring(_font.begin(), _font.end());
	Font F(font.c_str(), GetFontSize(), FontStyleRegular, UnitPixel);
	PointF P(GetPosition().X, GetPosition().Y);
	SolidBrush B(GetTextColor());
	StringFormat SF;
	SF.SetAlignment(StringAlignmentCenter);
	SF.SetLineAlignment(StringAlignmentCenter);

	std::string _text = GetText();
	std::wstring text = std::wstring(_text.begin(), _text.end());
	GameObject::Draw(g);
	g->DrawString(text.c_str(), -1, &F, P, &SF, &B);
}

void Text::Update(Graphics* g, DWORD tick)
{
	GameObject::Update(g, tick);
}
