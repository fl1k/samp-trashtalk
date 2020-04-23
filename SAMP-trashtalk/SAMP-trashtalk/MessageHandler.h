#pragma once
#include <cstdint>
#include <string>
#include "Config.h"
#include <vector>
#include <time.h>
#include "structs.h"
#include "Samp.h"

class MessageHandler
{
private:
	static std::vector<std::string> killMsgs;
	static std::vector<std::string> deathMsgs;
	static std::string GetRandomKillMsg();
	static std::string GetRandomDeathMsg();
	static const char* FormatMessage(std::string msg, Kill* kill);

public:
	static void Start();
	static void HookEvent();
	static void OnKill(Kill* lastKill, const char* localUsername);
	static void OnDeath(Kill* lastKill, const char* localUsername);
};

