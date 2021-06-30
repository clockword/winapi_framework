#pragma once
#include <map>
#include <list>
#include <stack>
#include <memory>

class GraphNode;
class DijkstraGraph
{
public:
	DijkstraGraph() : m_goalID(0) {}
	DijkstraGraph(const DijkstraGraph& other) {}
	~DijkstraGraph() {}

private:
	std::map<unsigned int, std::shared_ptr<GraphNode>> m_nodes;
	std::map<unsigned int, std::shared_ptr<GraphNode>> m_search;

	unsigned int m_goalID;

public:
	unsigned int InsertNode(float x, float y);

	std::list<GraphNode*>& Calculate(GraphNode* from, GraphNode* to);
	std::list<GraphNode*>& Calculate(unsigned int from, unsigned int to);

	GraphNode* GetNode(unsigned int id);


private:
	void Search(unsigned int id);
};

