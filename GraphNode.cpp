#include <limits>
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
	m_edges.insert(std::make_unique<EDGE>(this, toNode, cost));
}

bool GraphNode::MoveNextLowCostEdge()
{
	return m_edges.end() != ++m_currentEdge;
}

void GraphNode::MoveToLeastCostEdge()
{
	m_currentEdge = m_edges.begin();
}

bool GraphNode::HasEdge()
{
	return m_edges.begin() != m_edges.end();
}

void GraphNode::CompareAndInsert(EDGE* edge)
{
	if (m_shortestPath.empty())
	{
		m_shortestPath.push_back(edge->fromNode);
		m_shortestPath.push_back(edge->toNode);
		m_totalCost = edge->cost;
	}
	else
	{
		GraphNode* previousNode = m_shortestPath.back();
		float cost = previousNode->m_totalCost + edge->cost;
		if (cost < m_totalCost)
		{
			m_shortestPath.clear();
			m_shortestPath.insert(m_shortestPath.begin(),
				previousNode->m_shortestPath.begin(), previousNode->m_shortestPath.end());
			m_shortestPath.push_back(edge->toNode);
			m_totalCost = cost;
		}
	}
}

void GraphNode::ResetCost()
{
	m_totalCost = std::numeric_limits<float>::infinity();
}

void GraphNode::Clear()
{
	m_edges.clear();
}
