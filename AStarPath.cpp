#include <ctime>

#include "AStarPath.h"

AStarPath::AStarPath() : GameObject()
{
}

AStarPath::~AStarPath()
{
}

void AStarPath::Init()
{
	m_begin = Point(100, 100);
	m_end = Point(512, 384);
	m_astarGraph.InitNew(64, 48);
}

void AStarPath::Draw(Graphics* g)
{
	GameObject::Draw(g);

	Pen emptyPen(Color(0, 0, 0));
	SolidBrush beginBrush(Color(0, 255, 0));
	SolidBrush endBrush(Color(0, 0, 255));
	Pen pathPen(Color(255, 0, 255));
	SolidBrush blockBrush(Color(0, 0, 0));
	SolidBrush closedBrush(Color(255, 255, 0));
	for (int i = 0; i < 63; i++)
	{
		int x = i * 16 + 16;
		g->DrawLine(&emptyPen, x, 0, x, 768);
	}
	for (int i = 0; i < 47; i++)
	{
		int y = i * 16 + 16;
		g->DrawLine(&emptyPen, 0, y, 1024, y);
	}
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 48; y++)
		{
			if (m_astarGraph.GetNode(x, y)->isBlocked)
			{
				g->FillRectangle(&blockBrush, x * 16, y * 16, 16, 16);
			}
			else if (m_astarGraph.GetNode(x, y)->isClosed)
			{
				g->FillRectangle(&closedBrush, x * 16, y * 16, 16, 16);
			}
		}
	}
	g->FillEllipse(&beginBrush, m_begin.X - 4, m_begin.Y - 4, 8, 8);
	g->FillEllipse(&endBrush, m_end.X - 4, m_end.Y - 4, 8, 8);
	AStarNode* lastNode = nullptr;
	for (auto path : m_shortest)
	{
		if (lastNode == nullptr)
		{
			lastNode = path;
			continue;
		}
		g->DrawLine(&pathPen, lastNode->x * 16 + 8, lastNode->y * 16 + 8,
			path->x * 16 + 8, path->y * 16 + 8);
		lastNode = path;
	}
}

void AStarPath::Calculate()
{
	Point begin = m_begin - Point(4, 4);
	Point end = m_end - Point(4, 4);

	m_shortest = m_astarGraph.Calculate(begin.X / 16, begin.Y / 16, end.X / 16, end.Y / 16);
}

void AStarPath::MoveEnd(int x, int y)
{
	m_end.X += x;
	m_end.Y += y;
}

void AStarPath::MoveBegin(int x, int y)
{
	m_begin.X += x;
	m_begin.Y += y;
}
