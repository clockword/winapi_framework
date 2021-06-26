#include "Collider.h"

Rect ColliderRect::GetRect()
{
	Rect rect(GetPosition(), m_size);
	rect.X = rect.X + GetLocalPosition().X - m_size.Width * 0.5;
	rect.Y = rect.Y + GetLocalPosition().Y - m_size.Height * 0.5;
	return rect;
}

void ColliderRect::Draw(Graphics* g)
{
#ifdef _DEBUG
	Pen pen(Color(255, 0, 0));
	Rect rect(GetPosition(), m_size);
	rect.X = rect.X + GetLocalPosition().X - m_size.Width * 0.5;
	rect.Y = rect.Y + GetLocalPosition().Y - m_size.Height * 0.5;
	g->DrawRectangle(&pen, rect);
#endif
}

void ColliderCircle::Draw(Graphics* g)
{
#ifdef _DEBUG
	Pen pen(Color(255, 0, 0));
	Rect rect(GetPosition(), Size(m_radius * 2, m_radius * 2));
	rect.X = rect.X + GetLocalPosition().X - m_radius;
	rect.Y = rect.Y + GetLocalPosition().Y - m_radius;
	g->DrawEllipse(&pen, rect);
#endif
}
