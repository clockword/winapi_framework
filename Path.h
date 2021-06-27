#pragma once
#include "GameObject.h"

class Path : public GameObject
{
protected:


public:
	Path() : GameObject() {}
	virtual ~Path() {}

	virtual void Update(Graphics* g, DWORD tick);
};

