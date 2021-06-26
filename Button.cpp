#include "Button.h"
#include "InputManager.h"

void Button::Draw(Graphics* g)
{
	std::string _font = GetFont();
	std::wstring font = std::wstring(_font.begin(), _font.end());
	Font F(font.c_str(), GetFontSize() * GetFontScale(), FontStyleRegular, UnitPixel);
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

void Button::MouseWork()
{
	int mouseX = InputManager::GetInstance()->GetMouseMovePos().first;
	int mouseY = InputManager::GetInstance()->GetMouseMovePos().second;

	if (GetOriginalImageRect().Contains(Point(mouseX, mouseY)))
	{
		if (InputManager::GetInstance()->GetMouseClick())
		{
			SetScale(SizeF(1.2f, 1.2f));
			SetFontScale(1.2f);
			SetButtonClicked(true);
		}
		else
		{
			SetScale(SizeF(1.5f, 1.5f));
			SetFontScale(1.5f);
			SetButtonClicked(false);
		}
	}
	else
	{
		SetScale(SizeF(1.0f, 1.0f));
		SetFontScale(1.0f);
		SetButtonClicked(false);
	}
}

void Button::OnMouseButtonDown(int x, int y)
{
	if (GetOriginalImageRect().Contains(Point(x, y)))
	{
		
	}
}

void Button::OnMouseButtonUp(int x, int y)
{
	if (GetOriginalImageRect().Contains(Point(x, y)))
	{
		if (GetButtonClicked())
		{
			if (OnButton != nullptr || m_ctx != nullptr)
				OnButton(m_ctx, m_index);
		}
	}
}

void Button::Update(Graphics* g, DWORD tick)
{
	MouseWork();
	GameObject::Update(g, tick);
}
