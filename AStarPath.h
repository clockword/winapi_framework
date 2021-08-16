#pragma once

#include "GameObject.h"
#include "AStarGraph.h"

class AStarPath : public GameObject
{
public:
	AStarPath();
	virtual ~AStarPath();

private:
	AStarGraph m_astarGraph;
	Point m_begin;
	Point m_end;

	ASTARNODELIST m_shortest;

public:
	virtual void Init()override;
	virtual void Draw(Graphics* g)override;

	void SetBegin(Point point);
	void SetEnd(Point point);

	Point GetBegin()const { return m_begin; }
	Point GetEnd()const { return m_end; }

	void Calculate();

	AStarGraph* GetGraph() { return &m_astarGraph; }

};

