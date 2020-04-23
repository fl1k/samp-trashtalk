#pragma once
#include <iostream>

struct Kill
{
	char killer[25];
	char victim[25];
	char notNeeded1[4];
	char notNeeded2[4];
	uint8_t	byteType;
};

struct KillList
{
	char notNeeded[4];
	struct Kill kills[5];
};

