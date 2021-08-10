#pragma once
#include <queue>
#include <list>
#include <memory>
#include <vector>
#include <set>

class AStarGraph
{
public:
	struct AStarNode
	{
		typedef std::shared_ptr<AStarNode> NODEPTR;
		int x, y, f, g, h;
		bool isClosed;
		std::list<NODEPTR> accessibleNodes;
		NODEPTR parent;

		bool operator<(const AStarNode& other)
		{
			return f < other.f;
		}
	};

public:
	typedef AStarNode::NODEPTR NODEPTR;

private:
	struct NODECMP
	{
		bool operator()(const NODEPTR& node1, const NODEPTR& node2)const
		{
			return node1->f > node2->f;
		}
	};

	typedef std::vector<NODEPTR> NODEARR;
	typedef std::vector<NODEARR> NODEARR2;
	typedef std::priority_queue<NODEPTR, NODEARR, NODECMP> NODEPQ;

public:
	typedef std::list<NODEPTR> NODELIST;

public:
	AStarGraph(){}
	AStarGraph(const AStarGraph& other){}
	~AStarGraph(){}

private:
	NODEARR2 m_nodesArr;
	NODEPQ m_nodesQ;

public:
	void Init(int row, int col);
	NODELIST& Calculate(const NODEPTR& start, const NODEPTR& end);
	NODELIST& Calculate(int bx, int by, int ex, int ey);

private:
	int G(const NODEPTR& node, const NODEPTR& current)const;
	int H(const NODEPTR& node, const NODEPTR& end)const;
	bool Compare(const NODEPTR& node1, const NODEPTR& node2)const;

};

typedef AStarGraph::AStarNode AStarNode;
typedef AStarGraph::NODEPTR AStarNodePtr;
typedef AStarGraph::NODELIST AStarNodeList;