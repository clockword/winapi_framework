#pragma once
#include <map>
#include <list>
#include <stack>

class GraphNode;
class DijkstraGraph
{
public:
	DijkstraGraph() : m_goalID(0) {}
	DijkstraGraph(const DijkstraGraph& other) {}
	~DijkstraGraph() {}

private:
	std::map<unsigned int, GraphNode*> m_nodes;
	std::map<unsigned int, GraphNode*> m_search;

	unsigned int m_goalID;

public:
	void Calculate(GraphNode* from, GraphNode* to, std::list<GraphNode*>& path);
	void Calculate(unsigned int from, unsigned int to, std::list<GraphNode*>& path);

private:
	void Search(unsigned int id);
	void ClearStack();
};

