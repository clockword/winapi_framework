#pragma once
#include "Text.h"
#include <string>

class Button : public Text
{
private:
	float m_fontScale;
	bool m_buttonClick;

	void* m_ctx;
	int m_index;

protected:
	virtual void Draw(Graphics* g);

	virtual void MouseWork();
	void SetButtonClicked(bool clicked) { m_buttonClick = clicked; }
	bool GetButtonClicked() { return m_buttonClick; }

public:
	Button() : Text(), m_fontScale(1.0f), m_buttonClick(false), OnButton(nullptr), m_ctx(nullptr), m_index(-1) {}
	virtual ~Button() {}

	void SetFontScale(float scale) { m_fontScale = scale; }
	float GetFontScale() { return m_fontScale; }

	virtual void OnMouseButtonDown(int x, int y);
	virtual void OnMouseButtonUp(int x, int y);

	virtual void Update(Graphics* g, DWORD tick);

	void RegisterButtonFunc(void* func, void* ctx, int index) { OnButton = (void(*)(void*, int))func; m_ctx = ctx; m_index = index; }
	void (*OnButton)(void*, int);
};

