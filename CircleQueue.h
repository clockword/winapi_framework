#pragma once
#include "packet.h"

class CircleQueue
{
private:
	char* m_pQueue;
	int m_sFront;
	int m_sRear;

public:
	CircleQueue();
	virtual ~CircleQueue();

	void Clear() { m_sRear = m_sFront = 0; }
	void Init();

	int Push(char* data, short size);
	void Pop(short size) { m_sFront += size; }

	PACKETHEADER* GetPacket();
};

