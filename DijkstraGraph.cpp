#include <algorithm>
#include <limits>
#include "DijkstraGraph.h"
#include "GraphNode.h"

unsigned int DijkstraGraph::InsertNode(float x, float y)
{
	auto node = std::make_shared<GraphNode>(x, y);
	unsigned int id = node->GetId();
	m_nodes.insert({ id, node });
	return id;
}

std::list<GraphNode*>& DijkstraGraph::Calculate(GraphNode* from, GraphNode* to)
{
	m_goalID = to->GetId();

	for (auto node : m_nodes)
	{
		node.second->ResetCost();
	}
	from->ZeroCost();
	m_search.clear();
	//std::copy(m_nodes.begin(), m_nodes.end(), m_search.begin());

	Search(from->GetId());

	return to->GetShortestPath();
}

std::list<GraphNode*>& DijkstraGraph::Calculate(unsigned int from, unsigned int to)
{
	return Calculate(m_nodes[from].get(), m_nodes[to].get());
}

GraphNode* DijkstraGraph::GetNode(unsigned int id)
{
	return m_nodes[id].get();
}

void DijkstraGraph::Search(unsigned int id)
{
	const auto node = m_nodes[id];

	node->CalculateEdges();
	
	m_search.erase(id);

	if (!m_search.empty() && id != m_goalID)
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
