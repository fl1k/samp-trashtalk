#include "Samp.h"

uintptr_t Samp::sampModuleAddr;
uintptr_t Samp::sayFuncOffset;
uintptr_t Samp::addToChatFuncOffset;
uintptr_t Samp::localPlayerUsernameOffset;
uintptr_t Samp::updateKillListFuncOffset;
uintptr_t Samp::killListStart;

void Samp::Say(const char* message)
{
	uintptr_t sayFuncAddr = Samp::sampModuleAddr + Samp::sayFuncOffset;
	__asm
	{
		push message
		call sayFuncAddr
	}
}

const char* Samp::GetLocalUsername() 
{
	return (char*)(sampModuleAddr + localPlayerUsernameOffset);
}

Kill* Samp::GetLastKill()
{
	return ((Kill*)((*(uintptr_t*)(Samp::sampModuleAddr + Samp::killListStart)) + 0x4) + 4);
	/*
	Kill* lastKill = (Kill*)((*(uintptr_t*)(Samp::sampModuleAddr + Samp::killListStart)) + 0x4);
	for (int i = 0; i < 4; i++)
	{
		if (lastKill->killed != "")
			break;
		lastKill = (lastKill+1);
	}
	return lastKill;*/
}
