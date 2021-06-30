#include "DijkstraPath.h"
#include "GraphNode.h"
#include "AISettings.h"

void DijkstraPath::Draw(Graphics* g)
{
	GameObject::Draw(g);
	Pen pen = Pen(Color(255, 0, 0));
	g->DrawLines(&pen, m_points, m_pointCount);
}

void DijkstraPath::Update(Graphics* g, DWORD tick)
{
	GameObject::Update(g, tick);
}

void DijkstraPath::SetPathToPoint()
{
	
}
