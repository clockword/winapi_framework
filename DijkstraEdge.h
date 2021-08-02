#pragma once

class DijkstraNode;
struct DijkstraEdge
{
	DijkstraNode* fromNode;
	DijkstraNode* toNode;
	float cost;

	DijkstraEdge(DijkstraNode* from, DijkstraNode* to, float cost)
		: fromNode(from), toNode(to), cost(cost) {}
	DijkstraEdge(const DijkstraEdge& other) : fromNode(other.fromNode)
		, toNode(other.toNode), cost(other.cost) {}
	~DijkstraEdge() {}

	void operator= (const DijkstraEdge& other) noexcept
	{ fromNode = other.fromNode; toNode = other.toNode; cost = other.cost; }
};

inline bool operator==(const DijkstraEdge& e1, const DijkstraEdge& e2)
{
	return (e1.fromNode == e2.fromNode) && (e1.toNode == e2.toNode) && (e1.cost == e2.cost);
}

inline bool operator<(const DijkstraEdge& e1, const DijkstraEdge& e2)
{
	return e1.cost < e2.cost;
}