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
	m_astarGraph.InitNew(64, 48);
}

void AStarPath::Draw(Graphics* g)
{
}

void AStarPath::SetBegin(Point point)
{
	m_begin = point;
}

void AStarPath::SetEnd(Point point)
{
	m_end = point;
}

void AStarPath::Calculate()
{
	m_shortest = m_astarGraph.Calculate(m_begin.X, m_begin.Y, m_end.X, m_end.Y);
}
