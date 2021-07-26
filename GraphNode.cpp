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
}

void GraphNode::CalculateEdges()
{
	EDGESET::iterator it = m_edges.begin();
	for (; it != m_edges.end(); it++)
	{
		if (m_shortestPath.empty())
		{
			m_shortestPath.push_back((*it)->fromNode);
			m_shortestPath.push_back((*it)->toNode);
			m_totalCost = (*it)->cost;
		}
		else
		{
			GraphNode* previousNode = m_shortestPath.back();
			const float cost = previousNode->m_totalCost + (*it)->cost;
			if (cost < m_totalCost)
			{
				m_shortestPath.clear();
				m_shortestPath.insert(m_shortestPath.begin(),
					previousNode->m_shortestPath.begin(), previousNode->m_shortestPath.end());
				m_shortestPath.push_back((*it)->toNode);
				m_totalCost = cost;
			}
		}
	}
}

void GraphNode::Clear()
{
	m_edges.clear();
}
