#pragma once
#include <queue>
#include <memory>

class AStarNode;
class AStarGraph
{
private:
	AStarGraph(){}
	AStarGraph(const AStarGraph& other){}
	~AStarGraph(){}

private:
	typedef std::shared_ptr<AStarNode> NODEPTR;
	typedef std::vector<NODEPTR> NODEARR;
	typedef std::vector<std::vector<NODEPTR>> NODEARR2;
	typedef std::priority_queue<NODEPTR> NODEPQ;

private:
	NODEARR2 m_nodesArr;
	NODEPQ m_nodesQ;
	NODEPTR m_currentNode;
	NODEPTR m_endNode;

public:
	void Init(int row, int col);
	void Calculate(NODEPTR start, NODEPTR end);

private:
	int G(NODEPTR node);
	int H(NODEPTR node);

	
};

