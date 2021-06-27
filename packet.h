#pragma once

#pragma pack(push, 1)

typedef struct _tgPACKETHEADER
{
	unsigned int pktID;
	unsigned int size;
	unsigned int userID;
}PACKETHEADER, *LPPACKETHEADER;

#pragma pack(pop)