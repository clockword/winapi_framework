#include "DijkstraPath.h"
#include "GraphNode.h"
#include "AISettings.h"

void DijkstraPath::Init()
{
}

void DijkstraPath::Draw(Graphics* g)
{
	GameObject::Draw(g);

	Pen edgePen(Color(255, 0, 0));
	Pen nodePen(Color(0, 0, 255));

	std::set<std::unique_ptr<EDGE>>::iterator it;
	std::set<std::unique_ptr<EDGE>>::iterator end;

	auto nodes = m_dijkstraGraph.GetNodes();
	for (auto pair : *nodes)
	{
		GraphNode* node = pair.second.get();
		g->DrawEllipse(&nodePen, Rect(node->GetPosX() - 5, node->GetPosY() - 5, 5, 5));
		it = node->GetEdges()->begin();
		end = node->GetEdges()->end();
		for (; it != end; it++)
		{
			g->DrawLine(&edgePen, (*it)->fromNode->GetPosX(), (*it)->fromNode->GetPosY(),
				(*it)->toNode->GetPosX(), (*it)->toNode->GetPosY());
		}
	}
}
