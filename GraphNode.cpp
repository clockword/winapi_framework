#include <limits>
#include <Windows.h>

#include "GraphNode.h"
#include "AISettings.h"

unsigned int GraphNode::m_totalNode = 0;

void GraphNode::InsertEdge(GraphNode* toNode, float cost)
{
	m_edges.insert(std::make_unique<EDGE>(this, toNode, cost));
}

void GraphNode::InsertEdge(GraphNode* toNode)
{
	float cost = sqrtf(powf(m_posX - toNode->m_posX, 2) + powf(m_posY - toNode->m_posY, 2));
	EDGESET::iterator it = m_edges.begin();
	bool insertable = true;
	for (; it != m_edges.end(); it++)
	{
		if ((*it)->toNode == toNode)
		{
			insertable = false;
			break;
		}
	}
	if(insertable) m_edges.insert(std::make_unique<EDGE>(this, toNode, cost));
}

bool GraphNode::DeleteEdge(GraphNode* toNode)
{
	EDGESET::iterator it = m_edges.begin();
	for (; it != m_edges.end(); it++)
	{
		if ((*it)->toNode == toNode)
		{
			m_edges.erase(*it);
			return true;
		}
	}
	return false;
}

void GraphNode::DeleteAll()
{
	m_edges.clear();
}

void GraphNode::ResetCost()
{
	m_totalCost = std::numeric_limits<float>::infinity();
	m_shortestPath.clear();
}

void GraphNode::ZeroCost()
{
	m_totalCost = 0.0f;
	m_shortestPath.push_back(this);
}

void GraphNode::CalculateEdges()
{
	EDGESET::iterator it = m_edges.begin();
	for (; it != m_edges.end(); it++)
	{
		GraphNode* next = (*it)->toNode;
		const float cost = m_totalCost + (*it)->cost;
		if (next->m_shortestPath.empty())
		{
			next->m_shortestPath.insert(next->m_shortestPath.begin(),
				m_shortestPath.begin(), m_shortestPath.end());
			next->m_shortestPath.push_back(next);
			next->m_totalCost = cost;
		}
		else if (cost < next->m_totalCost)
		{
			next->m_shortestPath.clear();
			next->m_shortestPath.insert(next->m_shortestPath.begin(),
				m_shortestPath.begin(), m_shortestPath.end());
			next->m_shortestPath.push_back(next);
			next->m_totalCost = cost;
		}
	}
}

void GraphNode::Clear()
{
	m_edges.clear();
}
