#pragma once
#include <set>
#include <list>
#include <memory>
#include "DijkstraEdge.h"

class DijkstraNode
{
public:
	DijkstraNode() : m_id(m_totalNode++), m_posX(0.0f), m_posY(0.0f), 
		m_totalCost(0.0f) {}
	DijkstraNode(float x, float y) : m_id(m_totalNode++), 
		m_posX(x), m_posY(y), m_totalCost(0.0f) {}
	DijkstraNode(const DijkstraNode& other) : m_id(m_totalNode++),
		m_posX(other.m_posX), m_posY(other.m_posY), m_totalCost(0.0f) {}
	~DijkstraNode() {}

private:
	typedef std::set<std::unique_ptr<DijkstraEdge>> EDGESET;

private:
	static unsigned int m_totalNode;
	unsigned int m_id;
	EDGESET m_edges;

	float m_posX;
	float m_posY;

	float m_totalCost;
	std::list<DijkstraNode*> m_shortestPath;

public:
	unsigned int GetId()const { return m_id; }
	void InsertEdge(DijkstraNode* toNode, float cost);
	void InsertEdge(DijkstraNode* toNode);
	bool DeleteEdge(DijkstraNode* toNode);
	void DeleteAll();
	EDGESET* GetEdges() { return &m_edges; }
	void Clear();
	void CalculateEdges();

	void ResetCost();
	void ZeroCost();
	float GetCost()const { return m_totalCost; }
	
	/*left x, right y*/
	std::pair<float, float> GetPosition()const { return { m_posX, m_posY }; }
	float GetPosX()const { return m_posX; }
	float GetPosY()const { return m_posY; }

	std::list<DijkstraNode*>& GetShortestPath() { return m_shortestPath; }

	static void ZeroNode() { m_totalNode = 0; }
};

