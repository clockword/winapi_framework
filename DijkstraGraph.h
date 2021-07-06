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
	typedef std::map<unsigned int, std::shared_ptr<GraphNode>> NODEMAP;

private:
	NODEMAP m_nodes;
	NODEMAP m_search;

	unsigned int m_goalID;

public:
	/*Return node's id*/
	unsigned int InsertNode(float x, float y);

	std::list<GraphNode*>& Calculate(GraphNode* from, GraphNode* to);
	std::list<GraphNode*>& Calculate(unsigned int from, unsigned int to);

	GraphNode* GetNode(unsigned int id);
	NODEMAP* GetNodes() { return &m_nodes; }

private:
	void Search(unsigned int id);
};

