#pragma once
#include <queue>
#include <list>
#include <vector>
#include <set>

class AStarGraph
{
public:
	struct AStarNode
	{
		int x, y, f, g, h;
		bool isClosed, isBlocked;
		std::list<AStarNode*> accessibleNodes;
		AStarNode* parent;

		AStarNode() = delete;
		AStarNode(int x, int y);
		AStarNode(const AStarNode& other);
		~AStarNode() = default;

		bool operator<(const AStarNode& other)const;
	};

private:
	struct NODECMP
	{
		bool operator()(const AStarNode* node1, const AStarNode* node2)const;
	};

	typedef std::vector<AStarNode*> NODEARR;
	typedef std::vector<NODEARR> NODEARR2;
	typedef std::priority_queue<AStarNode*, NODEARR, NODECMP> NODEPQ;

public:
	typedef std::list<AStarNode*> NODELIST;

public:
	AStarGraph();
	AStarGraph(const AStarGraph& other);
	~AStarGraph();

private:
	int m_maxRow;
	int m_maxCol;
	NODEARR2 m_nodesArr;
	NODELIST m_shortestPath;

public:
	void InitNew(int row, int col);
	bool BlockNode(int x, int y);

	NODELIST& Calculate(AStarNode* const start, AStarNode* const end);
	NODELIST& Calculate(int bx, int by, int ex, int ey);

private:
	int G(const AStarNode* node, const AStarNode* current)const;
	int H(const AStarNode* node, const AStarNode* end)const;
	bool Compare(const AStarNode* node1, const AStarNode* node2)const;

	void Clear();
	void Release();

};

typedef AStarGraph::AStarNode AStarNode;
typedef AStarGraph::NODELIST ASTARNODELIST;