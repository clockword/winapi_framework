#include "AStarGraph.h"

AStarGraph::AStarNode::AStarNode(int x, int y)
{
	isClosed = false;
	isBlocked = false;
	this->x = x;
	this->y = y;
	g = 0;
	h = 0;
	f = 0;
	parent = nullptr;
}

AStarGraph::AStarNode::AStarNode(const AStarNode& other)
{
	isClosed = other.isClosed;
	isBlocked = other.isBlocked;
	x = other.x;
	y = other.y;
	g = other.g;
	h = other.h;
	f = other.f;
	parent = other.parent;
}

bool AStarGraph::AStarNode::operator<(const AStarNode& other)const
{
	return f < other.f;
}

bool AStarGraph::NODECMP::operator()(const AStarNode* node1, const AStarNode* node2) const
{
	return node1->f > node2->f;
}

AStarGraph::AStarGraph()
{
	m_maxRow = 0;
	m_maxCol = 0;
}

AStarGraph::AStarGraph(const AStarGraph& other)
{
	InitNew(other.m_maxRow, other.m_maxCol);
}

AStarGraph::~AStarGraph()
{
	Release();
}

void AStarGraph::InitNew(int row, int col)
{
	m_maxRow = row;
	m_maxCol = col;

	Release();

	for (int x = 0; x < row; x++)
	{
		NODEARR temp;
		for (int y = 0; y < col; y++)
		{
			AStarNode* const node = new AStarNode(x, y);
			temp.push_back(node);
		}
		m_nodesArr.push_back(temp);
	}
	for (const NODEARR& arr : m_nodesArr)
	{
		for (AStarNode* const node : arr)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					const int x = node->x + i;
					const int y = node->y + j;
					if ((i == 0 && j == 0) ||
						(x < 0 || x >= row) ||
						(y < 0 || y >= col))
						continue;
					node->accessibleNodes.push_back(m_nodesArr[x][y]);
				}
			}
		}
	}
}

bool AStarGraph::BlockNode(int x, int y)
{
	if (x < 0 || x >= m_maxRow || y < 0 || y > m_maxCol)
	{
		return false;
	}
	m_nodesArr[x][y]->isBlocked = true;

	return true;
}

AStarGraph::NODELIST& AStarGraph::Calculate(AStarNode* const start, AStarNode* const end)
{
	if (start->isBlocked ||
		end->isBlocked ||
		Compare(start, end))
	{
		m_shortestPath.clear();
		return m_shortestPath;
	}
	Clear();

	NODEPQ nodesQ;

	start->h = H(start, end);
	start->f = start->h;
	nodesQ.push(start);

	while (!nodesQ.empty())
	{
		AStarNode* const node = nodesQ.top();
		bool isNodeEnd = false;
		nodesQ.pop();

		node->isClosed = true;

		for (AStarNode* const next : node->accessibleNodes)
		{
			if (next->isClosed || next->isBlocked) continue;
			if (next->f > 0)
			{
				if (next->g > G(next, node))
				{
					next->g = G(next, node);
					next->f = next->g + next->h;
					next->parent = node;
				}
			}
			else
			{
				next->g = G(next, node);
				next->h = H(next, end);
				next->f = next->g + next->h;
				next->parent = node;

				nodesQ.push(next);
			}
			
			if (Compare(next, end))
			{
				isNodeEnd = true;
				break;
			}
		}
		if (isNodeEnd) break;
	}

	m_shortestPath.clear();
	AStarNode* it = end;
	while (it != nullptr)
	{
		m_shortestPath.emplace_front(it);
		it = it->parent;
	}
	return m_shortestPath;
}

AStarGraph::NODELIST& AStarGraph::Calculate(int bx, int by, int ex, int ey)
{
	if (bx < 0 || bx >= m_maxRow || by < 0 || by > m_maxCol ||
		ex < 0 || ex >= m_maxRow || ey < 0 || ey > m_maxCol)
	{
		m_shortestPath.clear();
		return m_shortestPath;
	}

	return Calculate(m_nodesArr[bx][by], m_nodesArr[ex][ey]);
}

int AStarGraph::G(const AStarNode* node, const AStarNode* current)const
{
	int g = 0;
	if ((current->x != node->x) && (current->y != node->y))
		g = 14;
	else
		g = 10;
	return node->g + g;
}

int AStarGraph::H(const AStarNode* node, const AStarNode* end)const
{
	return (abs(end->x - node->x) + abs(end->y - node->y)) * 10;
}

bool AStarGraph::Compare(const AStarNode* node1, const AStarNode* node2)const
{
	return (node1->x == node2->x) && (node1->y == node2->y);
}

void AStarGraph::Clear()
{
	for (const NODEARR& arr : m_nodesArr)
	{
		for (AStarNode* const node : arr)
		{
			node->isClosed = false;
			node->g = 0;
			node->h = 0;
			node->f = 0;
			node->parent = nullptr;
		}
	}
}

void AStarGraph::Release()
{
	for (NODEARR& const arr : m_nodesArr)
	{
		for (const AStarNode* node : arr)
		{
			delete node;
		}
		arr.clear();
	}
	m_nodesArr.clear();
}