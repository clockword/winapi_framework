#pragma once

#include <map>
#include <vector>
#include <string>
#include <Windows.h>

#include "CollObject.h"

class World final
{
private:
	typedef std::vector<CollObject*> CollObjectArr;
	typedef std::map<std::string, CollObjectArr> CollObjectMap;
	CollObjectMap m_collObjects;
	CollObjectMap m_colCheckMap;

private:
	World() {}

	World(const World&);
	World& operator=(World&);

private:
	void PushCheckMap(std::string tag, CollObjectArr push);
	void CollisionProcess(CollObject* object, CollObject* check, Point& movePos, DWORD tick);

public:
	static World* GetInstance();

	void Init();
	void FixedUpdate(DWORD tick);

	void RegisterCollObject(std::string tag, CollObject* object);
	void ClearRegistered();
};

