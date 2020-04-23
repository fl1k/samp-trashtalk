#include "Hook.h"

Hook::Hook(BYTE* src, BYTE* dst, int len)
{
	this->src = src;
	this->dst = dst;
	this->len = len;
	this->hookPlaced = false;
}


bool Hook::Place()
{
	DWORD currentProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &currentProtection);
	memcpy(defBytes, src, len);
	memset(src, 0x90, len);
	uintptr_t relativeAddress = (dst - src) - 0x5;
	*src = 0xE9;
	*(uintptr_t*)(src + 1) = relativeAddress;
	VirtualProtect(src, len, currentProtection, &currentProtection);
	hookPlaced = true;
	return true;
}

void* Hook::PlaceTrampoline()
{
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy_s(gateway, len, src, len);
	uintptr_t gatewayRelativeAddr = (src - gateway) - 0x5;
	*(gateway + len) = 0xE9;
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;
	Place();
	return gateway;
}

bool Hook::Undo()
{
	if (hookPlaced == false)
		return false;

	DWORD oldProtect;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(src, defBytes, len);
	VirtualProtect(src, len, oldProtect, &oldProtect);

	hookPlaced = false;
	return true;
}
