#pragma once

#include "Button.h"
#include <iostream>

class TextBox : public Button
{
public:
	enum class TextType
	{
		Default,
		IP_NUMBER,
		SHORT_NUMBER,
		ONLY_NUMBER,
	};

private:
	bool m_typeable;
	int m_textLimit;
	TextType m_textType;

protected:
	virtual void MouseWork();
	void ImageColorProcess();

public:
	TextBox() : Button(), m_typeable(false) {}
	virtual ~TextBox() {}

	virtual void OnMouseButtonDown(int x, int y);
	virtual void OnMouseButtonUp(int x, int y);
	void OnKeyboardInput(char ch);

	void SetTextLimit(int limit) { m_textLimit = limit; }

	void SetTextType(TextType type) { m_textType = type; }

	virtual void Update(Graphics* g, DWORD tick);
};

