#pragma once
#include <map>
#include <list>
#include <stack>
#include <memory>

class DijkstraNode;
class DijkstraGraph
{
public:
	DijkstraGraph();
	DijkstraGraph(const DijkstraGraph& other);
	~DijkstraGraph();

private:
	typedef std::map<unsigned int, std::shared_ptr<DijkstraNode>> NODEMAP;

private:
	NODEMAP m_nodes;
	NODEMAP m_search;

	unsigned int m_goalID;

public:
	/*Return node's id*/
	unsigned int InsertNode(float x, float y);

	std::list<DijkstraNode*>& Calculate(DijkstraNode* from, DijkstraNode* to);
	std::list<DijkstraNode*>& Calculate(unsigned int from, unsigned int to);

	DijkstraNode* GetNode(unsigned int id);
	NODEMAP* GetNodes() { return &m_nodes; }

	bool DeleteEdge(unsigned int from, unsigned to);
	bool DeleteNode(unsigned int id);

private:
	void Search(unsigned int id);
};

