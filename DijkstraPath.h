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
	bool m_beginSet;
	bool m_endSet;

	std::list<DijkstraNode*> m_shortest;

public:
	virtual void LoadExtra()override;
	virtual void Init()override;
	virtual void Draw(Graphics* g)override;

	void SetBeginID(unsigned int id);
	void SetEndID(unsigned int id);

	unsigned int GetBeginID()const { return m_beginID; }
	unsigned int GetEndID()const { return m_endID; }
	void CheckIsReset(unsigned int id);

	DWORD Calculate();

	DijkstraGraph* GetGraph() { return &m_dijkstraGraph; }
};

