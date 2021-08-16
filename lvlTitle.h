#pragma once

#include <string>

#include "Game.h"
#include "Level.h"

class lvlTitle final : public Level
{
private:
	enum class ButtonWork
	{
		DIJKSTRA_BASE,
		ASTAR_BASE,
	};

public:
	lvlTitle() = delete;
	lvlTitle(Game* game, std::string name);
	virtual ~lvlTitle();

	virtual void Init() override;
	virtual void Update(Graphics* g, DWORD tick) override;

	virtual void OnRecievePacket(void* packet) override;
	virtual void ButtonProcess(int index) override;

};