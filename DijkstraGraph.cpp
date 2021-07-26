#include <algorithm>
#include <limits>
#include <iterator>
#include "DijkstraGraph.h"
#include "GraphNode.h"

DijkstraGraph::DijkstraGraph() : m_goalID(0)
{
}

DijkstraGraph::DijkstraGraph(const DijkstraGraph& other)
{
}

DijkstraGraph::~DijkstraGraph()
{
	GraphNode::ZeroNode();
}

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

	for (auto &node : m_nodes)
	{
		node.second->ResetCost();
	}
	from->ZeroCost();
	m_search.clear();
	std::copy(m_nodes.begin(), m_nodes.end(), std::inserter(m_search, m_search.begin()));
	
	Search(from->GetId());

	return to->GetShortestPath();
}

std::list<GraphNode*>& DijkstraGraph::Calculate(unsigned int from, unsigned int to)
{
	return Calculate(m_nodes[from].get(), m_nodes[to].get());
}

GraphNode* DijkstraGraph::GetNode(unsigned int id)
{
	if (m_nodes.find(id) == m_nodes.end())
		return nullptr;
	return m_nodes[id].get();
}

bool DijkstraGraph::DeleteEdge(unsigned int from, unsigned to)
{
	if (m_nodes.find(from) == m_nodes.end())
		return false;
	if (m_nodes.find(from) == m_nodes.end())
		return false;

	return m_nodes[from]->DeleteEdge(m_nodes[to].get());
}

bool DijkstraGraph::DeleteNode(unsigned int id)
{
	if (m_nodes.find(id) == m_nodes.end())
		return false;

	GraphNode* delNode = m_nodes[id].get();

	delNode->DeleteAll();
	for (auto &node : m_nodes)
	{
		if (node.second == m_nodes[id])
			continue;
		node.second->DeleteEdge(delNode);
	}
	m_nodes.erase(id);

	return false;
}

void DijkstraGraph::Search(unsigned int id)
{
	const auto &node = m_nodes[id];

	node->CalculateEdges();
	
	m_search.erase(id);

	if (!m_search.empty() && id != m_goalID)
	{
		bool search = false;
		unsigned int nextSearch;
		float cost = std::numeric_limits<float>::max();
		for (auto &pair : m_search)
		{
			auto searchID = pair.first;
			auto &searchNode = pair.second;
			if (searchNode->GetCost() < cost)
			{
				cost = searchNode->GetCost();
				nextSearch = searchID;
				search = true;
			}
		}
		
		if (search) Search(nextSearch);
	}
}
