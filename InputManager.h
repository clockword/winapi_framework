#pragma once

#include <iostream>
#include <vector>

#include "Button.h"
#include "TextBox.h"

class InputManager final
{
private:
	typedef int X;
	typedef int Y;
	typedef std::vector<Button*> Buttons;
	typedef std::vector<TextBox*> TextBoxes;

	int m_x;
	int m_y;
	int m_xDown;
	int m_yDown;
	int m_xUp;
	int m_yUp;
	bool m_lMouseClicked;
	bool m_rMouseClicked;

	bool m_shockOff;

	Buttons buttons;
	TextBoxes textboxes;

private:
	InputManager();

	InputManager(InputManager&);
	InputManager& operator=(InputManager&);

public:

	static InputManager* GetInstance();

	void RegisterButton(Button* button);
	void RegisterTextBox(TextBox* textbox);
	void ClearRegistered();

	void SetMouseMovePos(int x, int y) { m_x = x; m_y = y; }
	void SetMouseDownPos(int x, int y);
	void SetMouseUpPos(int x, int y);
	void SetLMouseClick(bool click) { m_lMouseClicked = click; }
	void SetRMouseClick(bool click) { m_rMouseClicked = click; }
	void KeyBoardInput(char ch);

	std::pair<X, Y> GetMouseDownPos() { return std::make_pair(m_xDown, m_yDown); }
	std::pair<X, Y> GetMouseUpPos() { return std::make_pair(m_xUp, m_yUp); }
	std::pair<X, Y> GetMouseMovePos() { return std::make_pair(m_x, m_y); }
	bool GetLMouseClick() { return m_lMouseClicked; }
	bool GetRMouseClick() { return m_rMouseClicked; }

	void ShockOff() { m_shockOff = true; }
};

