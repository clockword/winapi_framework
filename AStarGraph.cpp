#include "AStarNode.h"
#include "AStarGraph.h"


void AStarGraph::Init(int row, int col)
{
	for (int x = 0; x < row; x++)
	{
		NODEARR arr;
		for (int y = 0; y < col; y++)
		{
			const NODEPTR& node = std::make_shared<AStarNode>(x, y);
			arr.push_back(node);
		}
		m_nodesArr.push_back(arr);
	}
}

void AStarGraph::Calculate(NODEPTR start, NODEPTR end)
{
	

	m_nodesQ.push(start);

	while (!m_nodesQ.empty())
	{
		const NODEPTR& node = m_nodesQ.top();
		m_nodesQ.pop();
		
	}
}

int AStarGraph::G(NODEPTR node)
{
	return 0;
}

int AStarGraph::H(NODEPTR node)
{
	return 0;
}
