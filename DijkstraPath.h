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

public:
	virtual void Init()override;
	virtual void Draw(Graphics* g)override;

	DijkstraGraph* GetGraph() { return &m_dijkstraGraph; }
};

