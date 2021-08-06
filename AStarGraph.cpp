#include "AStarGraph.h"

void AStarGraph::Init(int row, int col)
{
	for (int x = 0; x < row; x++)
	{
		NODEARR temp;
		for (int y = 0; y < col; y++)
		{
			const NODEPTR& node = std::make_shared<AStarNode>();
			node->x = x;
			node->y = y;
			node->g = 0;
			node->h = 0;
			node->f = 0;
			node->parent = nullptr;
			temp.push_back(node);
		}
		m_nodesArr.push_back(temp);
	}
	for (const NODEARR& arr : m_nodesArr)
	{
		for (const NODEPTR& node : arr)
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

AStarGraph::NODELIST& AStarGraph::Calculate(const NODEPTR& start, const NODEPTR& end)
{
	start->h = H(start, end);
	start->f = start->h;
	start->parent = nullptr;
	end->parent = nullptr;
	m_nodesQ.push(start);

	while (!m_nodesQ.empty())
	{
		NODEPTR node = m_nodesQ.top();
		if (Compare(node, end)) break;

		m_nodesQ.pop();

		for (const NODEPTR& next : node->accessibleNodes)
		{
			if (m_closed.find(next) != m_closed.end())
				continue;
			m_closed.insert(next);
			next->g = G(next, node);
			next->h = H(next, end);
			next->f = next->g + next->h;
			next->parent = node;
			if (Compare(node, end))
				break;
			m_nodesQ.push(next);
		}
	}

	NODELIST list;
	NODEPTR it = end;
	while (it != nullptr)
	{
		list.push_front(it);
		it = it->parent;
	}
	return list;
}

AStarGraph::NODELIST& AStarGraph::Calculate(int bx, int by, int ex, int ey)
{
	return Calculate(m_nodesArr[bx][by], m_nodesArr[ex][ey]);
}

int AStarGraph::G(const NODEPTR& node, const NODEPTR& current)const
{
	int g = 0;
	if ((current->x != node->x) && (current->y != node->y))
		g = 14;
	else
		g = 10;
	return node->g + g;
}

int AStarGraph::H(const NODEPTR& node, const NODEPTR& end)const
{
	return (abs(end->x - node->y) + abs(end->x - node->y)) * 10;
}

bool AStarGraph::Compare(const NODEPTR& node1, const NODEPTR& node2)const
{
	return (node1->x == node2->x) && (node1->y == node2->y);
}
