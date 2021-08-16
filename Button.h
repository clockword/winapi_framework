#pragma once

#include <string>
#include <functional>

#include "Text.h"

class Level;
class Button : public Text
{
private:
	float m_fontScale;
	bool m_buttonClick;

protected:
	virtual void Draw(Graphics* g);

	virtual void MouseWork();
	void SetButtonClicked(bool clicked) { m_buttonClick = clicked; }
	bool GetButtonClicked() { return m_buttonClick; }

public:
	Button() : Text(), m_fontScale(1.0f), m_buttonClick(false) {}
	virtual ~Button() {}

	void SetFontScale(float scale) { m_fontScale = scale; }
	float GetFontScale() { return m_fontScale; }

	virtual void OnMouseButtonDown(int x, int y);
	virtual void OnMouseButtonUp(int x, int y);

	virtual void Update(Graphics* g, DWORD tick);

	void RegisterButton(Level* level, int index);
	std::function<void()> OnButtonDown = nullptr;
};

