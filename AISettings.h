#pragma once

class GraphNode;
struct EDGE
{
	GraphNode* fromNode;
	GraphNode* toNode;
	float cost;

	EDGE(GraphNode* from, GraphNode* to, float cost)
		: fromNode(from), toNode(to), cost(cost) {}
	EDGE(const EDGE& other) : fromNode(other.fromNode)
		, toNode(other.toNode), cost(other.cost) {}
	~EDGE() {}

	void operator= (const EDGE& other) noexcept
	{ fromNode = other.fromNode; toNode = other.toNode; cost = other.cost; }
};

inline bool operator==(const EDGE& e1, const EDGE& e2) noexcept
{
	return (e1.fromNode == e2.fromNode) && (e1.toNode == e2.toNode) && (e1.cost == e2.cost);
}

inline bool operator<(const EDGE& e1, const EDGE& e2) noexcept
{
	return e1.cost < e2.cost;
}