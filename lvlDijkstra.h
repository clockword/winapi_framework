#pragma once

#include <string>

#include "Game.h"
#include "Level.h"

class lvlDijkstra final : public Level
{
private:
	enum class ButtonWork
	{
		TITLE,
		EDIT,
		EXECUTE,
		ADDEDGE,
		REMOVEEDGE,
		REMOVENODE,
		BEGIN,
		END,
		CALCULATE,
	};

private:
	bool editMode;
	bool isClickable;
	int newObjNum;

public:
	lvlDijkstra() = delete;
	lvlDijkstra(Game* game, std::string name);
	virtual ~lvlDijkstra();

	virtual void Init() override;
	virtual void Update(Graphics* g, DWORD tick) override;

	virtual void OnRecievePacket(void* packet) override;
	virtual void ButtonProcess(int index) override;

};

