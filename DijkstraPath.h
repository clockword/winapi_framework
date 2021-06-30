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
	PointF* m_points;
	int m_pointCount;

protected:
	virtual void Draw(Graphics* g);

public:
	virtual void Update(Graphics* g, DWORD tick);

	DijkstraGraph* GetGraph() { return &m_dijkstraGraph; }

	void SetPathToPoint();
};

