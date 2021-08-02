#pragma once
#include <list>

class AStarNode
{
private:
	int row;
	int col;
	int cost;
	std::list<AStarNode*> accessibleNodes;

public:
	AStarNode(int row, int col);
	AStarNode(const AStarNode& other);
	~AStarNode();

	bool operator==(const AStarNode& other);
	bool operator<(const AStarNode& other);
};