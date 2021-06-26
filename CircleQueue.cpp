#include "CircleQueue.h"
#include <memory.h>
#include <stdlib.h>

#define QUEUE_SIZE 10000

CircleQueue::CircleQueue()
{
	m_sRear = m_sFront = 0;
	m_pQueue = (char*)malloc(QUEUE_SIZE);
}

CircleQueue::~CircleQueue()
{
	free(m_pQueue);
}

void CircleQueue::Init()
{
	int size = m_sRear - m_sFront;
	memcpy(&m_pQueue[0], &m_pQueue[m_sFront], size);

	m_sFront = 0;
	m_sRear = size;
}

int CircleQueue::Push(char* data, short size)
{
	if (size == 0) return 0;
	if (size >= QUEUE_SIZE) return -1;

	if ((QUEUE_SIZE - m_sRear) <= size)
	{
		Init();
	}
	memcpy(&m_pQueue[m_sRear], data, size);

	m_sRear += size;

	return 1;
}

PACKETHEADER* CircleQueue::GetPacket()
{
	int size = m_sRear - m_sFront;
	if (size == 0) return (PACKETHEADER*)NULL;
	if (size < 8) return (PACKETHEADER*)NULL;

	int packet_size = (*((PACKETHEADER*)&m_pQueue[m_sFront])).size;
	if (size < packet_size) return (PACKETHEADER*)NULL;

	return (PACKETHEADER*)&m_pQueue[m_sFront];
}
