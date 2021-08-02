#include <limits>
#include <iterator>
#include "AStarNode.h"

AStarNode::AStarNode(int row, int col)
{
	this->row = row;
	this->col = col;
	cost = std::numeric_limits<int>::max();
}

AStarNode::AStarNode(const AStarNode& other)
{
	row = other.row;
	col = other.col;
	cost = other.cost;
	std::copy(other.accessibleNodes.begin(), other.accessibleNodes.end(),
		std::inserter(accessibleNodes, accessibleNodes.begin()));
}

AStarNode::~AStarNode()
{
}

bool AStarNode::operator==(const AStarNode& other)
{
	return (row == other.row) && (col == other.col);
}

bool AStarNode::operator<(const AStarNode& other)
{
	return cost < other.cost;
}
