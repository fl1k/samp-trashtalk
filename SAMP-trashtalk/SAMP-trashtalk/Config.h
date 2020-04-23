#pragma once
#include <cstdint>
#include <string>

class Config
{
public:
	static void Load();
	static bool DEBUG_MODE;
	static uintptr_t sayFuncOffset;
	static uintptr_t addToChatFuncOffset;
	static uintptr_t updateKillListFuncOffset;
	static uintptr_t jumpAfterKillListOffset;
	static uintptr_t killListStart;
	static uintptr_t localPlayerUsernameOffset;
	static bool sendOnKill;
	static std::string onKillMsgsPath;
	static bool sendOnDeath;
	static std::string onDeathMsgsPath;
};

