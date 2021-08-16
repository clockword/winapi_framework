#include "GameObject.h"
#include "Level.h"

GameObject::GameObject()
{
	m_image = nullptr;

	m_aniRect = nullptr;
	m_aniKind = 0;
	m_aniKindMax = 0;
	m_aniIndex = nullptr;
	m_aniIndexMax = nullptr;
	m_aniInterval = nullptr;
	m_aniIntervalMax = nullptr;
	
	m_x = 0;
	m_y = 0;
	m_xCenter = 0;
	m_yCenter = 0;
	m_sizeX = 1.0f;
	m_sizeY = 1.0f;
	m_rotation = 0.0f;
	m_active = true;
	m_imageColor = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			  	     0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				     0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				     0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	m_imgScale = SizeF(1.0f, 1.0f);
	m_vpLevel = nullptr;

	m_aniTimeCount = 0;
}

GameObject::~GameObject()
{
	m_image = nullptr;

	if (m_aniRect != nullptr)
	{
		for (DWORD i = 0; i < m_aniKindMax; i++)
			delete[] m_aniRect[i];
		delete[] m_aniRect;
	}

	if (m_aniIndex != nullptr)
		delete[] m_aniIndex;
	if (m_aniIndexMax != nullptr)
		delete[] m_aniIndexMax;
	if (m_aniInterval != nullptr)
		delete[] m_aniInterval;
	if (m_aniIntervalMax != nullptr)
		delete[] m_aniIntervalMax;
}

/*value must be 0.0f ~ 1.0f*/
void GameObject::SetColor(float r, float g, float b, float a)
{
	m_imageColor.m[0][0] = r;
	m_imageColor.m[1][1] = g;
	m_imageColor.m[2][2] = b;
	m_imageColor.m[3][3] = a;
}

float GameObject::GetAnimationNormalizedTime()
{
	return m_aniTimeCount / (m_aniIntervalMax[m_aniKind] * m_aniIndexMax[m_aniKind]);
}

void GameObject::SetFile(std::string filename)
{
	FILE* file = nullptr;

	std::string path = "./Resource/Anim/" + filename + ".txt";

	fopen_s(&file, path.c_str(), "rt");

	fscanf_s(file, "%d", &m_aniKindMax);
	m_aniRect = new Rect * [m_aniKindMax];
	m_aniIndex = new DWORD[m_aniKindMax];
	m_aniIndexMax = new DWORD[m_aniKindMax];
	m_aniInterval = new DWORD[m_aniKindMax];
	m_aniIntervalMax = new DWORD[m_aniKindMax];

	for (DWORD i = 0; i < m_aniKindMax; i++)
	{
		m_aniIndex[i] = 0;
		m_aniInterval[i] = 0;
		DWORD kind;
		fscanf_s(file, "%d %d %d", &kind, &m_aniIndexMax[i], &m_aniIntervalMax[i]);
		m_aniRect[i] = new Rect[m_aniIndexMax[i]];
		for (DWORD j = 0; j < m_aniIndexMax[i]; j++)
		{
			fscanf_s(file, "%d %d %d %d", &m_aniRect[i][j].X, &m_aniRect[i][j].Y,
				&m_aniRect[i][j].Width, &m_aniRect[i][j].Height);
		}
	}

	fclose(file);
}

void GameObject::SetImage(Image* image)
{
	m_image = image;
}

void GameObject::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void GameObject::SetPosition(Point position)
{
	m_x = position.X;
	m_y = position.Y;
}

void GameObject::Update(Graphics* g, DWORD tick)
{
	UpdateAnim(tick);
	Draw(g);
}

Rect GameObject::GetOriginalImageRect()
{
	int x = m_x - m_xCenter * m_sizeX;
	int y = m_y - m_yCenter * m_sizeY;
	INT sourceX = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].X;
	INT sourceY = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Y;
	INT sourceWidth = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Width;
	INT sourceHeight = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Height;

	Rect viewRect(x, y, sourceWidth * m_sizeX, sourceHeight * m_sizeY);

	return viewRect;
}

Rect GameObject::GetImageRect()
{
	int x = m_x - m_xCenter;
	int y = m_y - m_yCenter;
	INT sourceX = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].X;
	INT sourceY = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Y;
	INT sourceWidth = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Width;
	INT sourceHeight = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Height;

	Rect viewRect(x, y, sourceWidth, sourceHeight);

	return viewRect;
}

void GameObject::UpdateAnim(DWORD tick)
{
	m_aniTimeCount += tick;

	m_aniInterval[m_aniKind] += tick;

	if (m_aniInterval[m_aniKind] >= m_aniIntervalMax[m_aniKind])
	{
		m_aniInterval[m_aniKind] = 0;
		m_aniIndex[m_aniKind]++;
		if (m_aniIndex[m_aniKind] >= m_aniIndexMax[m_aniKind])
		{
			m_aniIndex[m_aniKind] = 0;
		}
	}

	SetCenter(GetImageRect().Width * 0.5, GetImageRect().Height * 0.5);
}

void GameObject::Draw(Graphics * g)
{
	int x = m_x - m_xCenter * m_sizeX * m_imgScale.Width;
	int y = m_y - m_yCenter * m_sizeY * m_imgScale.Height;
	INT sourceX = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].X;
	INT sourceY = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Y;
	INT sourceWidth = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Width;
	INT sourceHeight = m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Height;
	
	Rect viewRect(x, y, sourceWidth * m_sizeX * m_imgScale.Width, sourceHeight * m_sizeY * m_imgScale.Height);

	ImageAttributes attributes;
	attributes.SetColorMatrix(&m_imageColor);
	
	g->TranslateTransform((float)m_x, (float)m_y);

	g->RotateTransform(m_rotation);

	g->TranslateTransform(-(float)m_x, -(float)m_y);

	g->DrawImage(m_image, viewRect,
		sourceX,
		sourceY,
		sourceWidth,
		sourceHeight,
		Gdiplus::UnitPixel,
		&attributes);

	g->TranslateTransform((float)m_x, (float)m_y);

	g->RotateTransform(-m_rotation);

	g->TranslateTransform(-(float)m_x, -(float)m_y);
}

void GameObject::SetCenter(int x, int y)
{
	m_xCenter = x;
	m_yCenter = y;
}

void GameObject::MoveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}

void GameObject::MoveBy(int x, int y)
{
	m_x += x;
	m_y += y;
}

void GameObject::SetSize(float x, float y)
{
	m_sizeX = x;
	m_sizeY = y;
}
