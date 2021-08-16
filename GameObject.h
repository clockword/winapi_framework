#pragma once

#include <string>
#include <Windows.h>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

class Level;
class GameObject
{
private:
	Image* m_image;

	Rect **m_aniRect;
	DWORD m_aniKind;
	DWORD m_aniKindMax;
	DWORD*m_aniIndex;
	DWORD*m_aniIndexMax;
	DWORD*m_aniInterval;
	DWORD*m_aniIntervalMax;

	Level* m_vpLevel;

	int m_x;
	int m_y;
	int m_xCenter;
	int m_yCenter;
	float m_sizeX;
	float m_sizeY;
	float m_rotation;
	bool m_active;

	ColorMatrix m_imageColor;

	std::string m_tag;
	std::string m_name;

	SizeF m_imgScale;

	DWORD m_aniTimeCount;

protected:
	void SetCenter(int x, int y);
	void MoveTo(int x, int y);
	void MoveBy(int x, int y);
	Rect GetOriginalImageRect();
	Rect GetImageRect();
	void SetImageColor(ColorMatrix color) { m_imageColor = color; }
	ColorMatrix GetImageColor() { return m_imageColor; }
	Size GetSize() { return Size(m_sizeX, m_sizeY); }

	void UpdateAnim(DWORD tick);
	virtual void Draw(Graphics* g);
public:
	GameObject();
	virtual ~GameObject();

	virtual void LoadExtra() {}
	virtual void Init() {}

	void SetTag(std::string tag) { m_tag = tag; }
	std::string GetTag() { return m_tag; }
	inline void SetActive(bool active)noexcept { m_active = active; }
	inline bool GetActive()const noexcept { return m_active; }
	Point GetPosition() { return Point(m_x, m_y); }
	void SetPosition(int x, int y);
	void SetPosition(Point position);
	void SetRotation(float rotation) { m_rotation = rotation; }
	void Rotate(float rotation) { m_rotation += rotation; }
	float GetRotation() { return m_rotation; }
	void SetSize(float x, float y);
	void SetScale(SizeF scale) { m_imgScale = scale; }
	SizeF GetScale() { return m_imgScale; }
	void SetName(std::string name) { m_name = name; }
	std::string GetName() { return m_name; }
	void SetColor(float r, float g, float b, float a);
	void SetLevel(Level* level) { m_vpLevel = level; }
	void* GetLevel() { return m_vpLevel; }
	void SetAniKind(DWORD kind) { m_aniKind = kind; m_aniTimeCount = 0; }
	DWORD GetAniKind() { return m_aniKind; }
	/*현재 애니메이션의 진행율을 반환합니다.*/
	float GetAnimationNormalizedTime();
	void ResetAniIndex() { m_aniIndex[m_aniKind] = 0; }

	void SetFile(std::string filename);
	void SetImage(Image* image);
	virtual void SetCollider(std::string filename) {}

	virtual void Update(Graphics* g, DWORD tick);
};

