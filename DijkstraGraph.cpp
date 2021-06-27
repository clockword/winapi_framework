#include <algorithm>
#include <limits>
#include "DijkstraGraph.h"
#include "GraphNode.h"

void DijkstraGraph::Calculate(GraphNode* from, GraphNode* to, std::list<GraphNode*>& path)
{
	m_goalID = to->GetId();

	m_search.insert(m_nodes.begin(), m_nodes.end());
	Search(from->GetId());


}

void DijkstraGraph::Calculate(unsigned int from, unsigned int to, std::list<GraphNode*>& path)
{
	Calculate(m_nodes[from], m_nodes[to], path);
}

void DijkstraGraph::Search(unsigned int id)
{
	// wrong
	if (m_nodes[id]->HasEdge())
	{
		m_nodes[id]->MoveToLeastCostEdge();
		do
		{
			EDGE edge = m_nodes[id]->GetCurrentEdge();

			edge.toNode->AddCost(edge.cost);

		} while (m_nodes[id]->MoveNextLowCostEdge());
	}
	
	m_search.erase(id);

	if (!m_search.empty())
	{
		bool search = false;
		unsigned int nextSearch;
		float cost = std::numeric_limits<float>::max();
		for (auto pair : m_search)
		{
			auto searchID = pair.first;
			auto node = pair.second;
			if (node->GetCost() < cost)
			{
				cost = node->GetCost();
				nextSearch = searchID;
				search = true;
			}
		}

		if (search) Search(nextSearch);
	}
}
