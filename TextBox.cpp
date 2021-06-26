#include "TextBox.h"
#include "InputManager.h"
#include <conio.h>

void TextBox::MouseWork()
{
	int mouseX = InputManager::GetInstance()->GetMouseMovePos().first;
	int mouseY = InputManager::GetInstance()->GetMouseMovePos().second;

	if (GetOriginalImageRect().Contains(Point(mouseX, mouseY)))
	{
		if (InputManager::GetInstance()->GetMouseClick())
		{
			SetButtonClicked(true);
		}
		else
		{
			SetButtonClicked(false);
		}
	}
	else
	{
		SetButtonClicked(false);
	}
}

void TextBox::ImageColorProcess()
{
	ColorMatrix color = GetImageColor();

	if (m_typeable)
	{
		if (color.m[3][3] != 1.0f)
		{
			color.m[3][3] = 1.0f;
			SetImageColor(color);
		}
	}
	else
	{
		if (color.m[3][3] != 0.5f)
		{
			color.m[3][3] = 0.5f;
			SetImageColor(color);
		}
	}
}

void TextBox::OnMouseButtonDown(int x, int y)
{
	if (GetOriginalImageRect().Contains(Point(x, y)))
	{

	}
}

void TextBox::OnMouseButtonUp(int x, int y)
{
	if (GetOriginalImageRect().Contains(Point(x, y)))
	{
		if (GetButtonClicked())
		{
			m_typeable = true;
		}
		else
		{
			m_typeable = false;
		}
	}
	else
	{
		m_typeable = false;
	}
}

void TextBox::OnKeyboardInput(char ch)
{
	if (m_typeable)
	{
		std::string text = GetText();
		if (ch == 8)
		{
			if (!text.empty())
			{
				text.pop_back();
				SetText(text);
			}
			return;
		}

		switch (m_textType)
		{
		case TextBox::TextType::Default:
			if (text.size() < m_textLimit)
			{
				text.push_back(ch);
			}
			break;
		case TextBox::TextType::IP_NUMBER:
		{
			if ((ch >= '0' && ch <= '9' || ch == '.') && text.size() < 15)
			{
				text.push_back(ch);
			}
		}break;
		case TextBox::TextType::SHORT_NUMBER:
		{
			if ((ch >= '0' && ch <= '9') && text.size() < 5)
			{
				text.push_back(ch);
			}
			if (text.empty()) return;
			if (std::stoi(text) > 65535) text = "65535";
			else if (std::stoi(text) < 0) text = "0";
		}break;
		}

		SetText(text);
	}
}

void TextBox::Update(Graphics* g, DWORD tick)
{
	MouseWork();
	ImageColorProcess();
	GameObject::Update(g, tick);
}
