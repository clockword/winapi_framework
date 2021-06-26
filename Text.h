#pragma once
#include <string>

#include "GameObject.h"

class Text : public GameObject
{
private:
	std::string m_text;
	std::string m_font;
	Color m_textColor;
	int m_fontSize;
	
protected:
	virtual void Draw(Graphics* g);

	std::string GetFont() { return m_font; }
	Color GetTextColor() { return m_textColor; }
	int GetFontSize() { return m_fontSize; }

public:
	void SetText(std::string text) { m_text = text; }
	std::string GetText() { return m_text; }
	void SetFont(std::string font) { m_font = font; }
	void SetTextColor(Color color) { m_textColor = color; }
	void SetFontSize(int size) { m_fontSize = size; }

public:
	Text() : GameObject(), m_text("Test"), m_font("Segoe UI"),
		m_textColor(Color(0, 0, 0)), m_fontSize(48) {}
	virtual ~Text() {}

	virtual void Update(Graphics* g, DWORD tick);
};

