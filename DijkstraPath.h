#pragma once
#include "GameObject.h"
#include "DijkstraGraph.h"

class DijkstraPath : public GameObject
{
public:
	DijkstraPath() : GameObject() {}
	virtual ~DijkstraPath() {}

private:
	DijkstraGraph m_dijkstraGraph;
	unsigned int m_beginID;
	unsigned int m_endID;

public:
	virtual void LoadExtra()override;
	virtual void Init()override;
	virtual void Draw(Graphics* g)override;

	void SetBeginID(unsigned int id) { m_beginID = id; }
	void SetEndID(unsigned int id) { m_endID = id; }

	unsigned int GetBeginID() { return m_beginID; }
	unsigned int GetEndID() { return m_endID; }

	DijkstraGraph* GetGraph() { return &m_dijkstraGraph; }
};

