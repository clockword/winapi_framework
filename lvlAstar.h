#pragma once

#include <string>

#include "Game.h"
#include "Level.h"

class lvlAstar final : public Level
{
private:
	enum class ButtonWork
	{
		TITLE,
	};

public:
	lvlAstar() = delete;
	lvlAstar(Game* game, std::string name);
	virtual ~lvlAstar();

	virtual void Init() override;
	virtual void Update(Graphics* g, DWORD tick) override;

	virtual void OnRecievePacket(void* packet) override;
	virtual void ButtonProcess(int index) override;

private:
	void ExecuteInputs(DWORD tick);

};

