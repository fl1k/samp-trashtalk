#pragma once
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>

class Hook
{
private:
	BYTE defBytes[32];
	BYTE* src;
	BYTE* dst;
	int len;
	bool hookPlaced;

public:
	Hook(BYTE* src, BYTE* dst, int length);
	bool Place();
	bool Undo();
	void* PlaceTrampoline();
};