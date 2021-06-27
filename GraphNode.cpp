#include <limits>
#include "GraphNode.h"
#include "AISettings.h"

unsigned int GraphNode::m_totalNode = 0;

void GraphNode::InsertEdge(EDGE edge)
{
	m_edges.insert(edge);
}

void GraphNode::EraseEdge(EDGE edge)
{
	m_edges.erase(edge);
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

void GraphNode::AddCost(float cost)
{
	if (m_totalCost == std::numeric_limits<float>::infinity())
		m_totalCost = 0.0f;
	m_totalCost += cost;
}

void GraphNode::ResetCost()
{
	m_totalCost = std::numeric_limits<float>::infinity();
}

void GraphNode::Clear()
{
	m_edges.clear();
}
