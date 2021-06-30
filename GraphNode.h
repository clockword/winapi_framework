#pragma once
#include <set>
#include <tuple>
#include <list>
#include <memory>
#include "AISettings.h"

class GraphNode
{
public:
	GraphNode() : m_id(m_totalNode++), m_posX(0.0f), m_posY(0.0f), 
		m_totalCost(0.0f) {}
	GraphNode(float x, float y) : m_id(m_totalNode++), 
		m_posX(x), m_posY(y), m_totalCost(0.0f) {}
	GraphNode(const GraphNode& other) : m_id(m_totalNode++),
		m_posX(other.m_posX), m_posY(other.m_posY), m_totalCost(0.0f) {}
	~GraphNode() {}

private:
	static unsigned int m_totalNode;
	unsigned int m_id;
	std::set<std::unique_ptr<EDGE>> m_edges;
	std::set<std::unique_ptr<EDGE>>::iterator m_currentEdge;

	float m_posX;
	float m_posY;

	float m_totalCost;
	std::list<GraphNode*> m_shortestPath;

public:
	unsigned int GetId()const { return m_id; }
	void InsertEdge(GraphNode* toNode, float cost);
	void InsertEdge(GraphNode* toNode);
	void CompareAndInsert(EDGE* edge);
	bool HasEdge();
	void Clear();
	bool MoveNextLowCostEdge();
	void MoveToLeastCostEdge();
	
	EDGE* GetCurrentEdge()const { return m_currentEdge->get(); }
	void ResetCost();
	void ZeroCost() { m_totalCost = 0.0f; }
	float GetCost()const { return m_totalCost; }
	
	//void SetPosition(float x, float y) { m_posX = x; m_posY = y; }
	std::pair<float, float> GetPosition()const { return { m_posX, m_posY }; }

	std::list<GraphNode*>& GetShortestPath() { return m_shortestPath; }

};

