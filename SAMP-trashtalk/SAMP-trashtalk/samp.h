#include "structs.h"

class Samp
{
public:
	static uintptr_t sampModuleAddr;
	static uintptr_t sayFuncOffset;
	static uintptr_t killListStart;
	static uintptr_t addToChatFuncOffset;
	static uintptr_t updateKillListFuncOffset;
	static uintptr_t localPlayerUsernameOffset;
	static void Say(const char* msg);
	static const char* GetLocalUsername();
	static Kill* GetLastKill();
	//static void AddToChat();
};
