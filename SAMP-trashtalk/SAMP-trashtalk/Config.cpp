#include "Config.h"
#include <filesystem>
#include <string>
#include <fstream>
#include "json.hpp"
#include <iostream>

bool Config::DEBUG_MODE;
uintptr_t Config::sayFuncOffset;
uintptr_t Config::addToChatFuncOffset;
uintptr_t Config::updateKillListFuncOffset;
uintptr_t Config::localPlayerUsernameOffset;
uintptr_t Config::killListStart;;
uintptr_t Config::jumpAfterKillListOffset;
bool Config::sendOnKill;
std::string Config::onKillMsgsPath;
bool Config::sendOnDeath;
std::string Config::onDeathMsgsPath;

void Config::Load()
{
	std::ifstream ifStream("trashtalk\\config.json");
	if (!std::filesystem::exists("trashtalk"))
		std::filesystem::create_directory("trashtalk");
	nlohmann::json config;

	if (!ifStream.good())
	{
		std::ofstream ofStream("trashtalk\\config.json");
		config =
		{
		{"DEBUG_MODE", false},
	   {"sayFuncOffset", 0x57F0},
	   {"addToChatFuncOffset", 0x0},
	   {"updateKillListFuncOffset", 0x2B2A40},
	   {"localPlayerUsernameOffset", 0x219A6F},
	   {"killListStart", 0x0021A0EC},
	   {"jumpAfterKillListOffset", 0x26D6BA},
	   {"sendOnKill", true},
	   {"onKillMsgsPath", "onKillMsgs.txt"},
	   {"sendOnDeath", false},
	   {"onDeathMsgsPath", "onDeathMsgs.txt"} };

		ofStream << config;
		//std::cout << "Config file with defaults for 0.3.7 R1 generated successfully\n";
	}
	else
	{
		ifStream >> config;
		if (config["DEBUG_MODE"] == true)
			std::cout << "Config file imported successfully\n";
	}
	sayFuncOffset = config["sayFuncOffset"];
	addToChatFuncOffset = config["addToChatFuncOffset"];
	updateKillListFuncOffset = config["updateKillListFuncOffset"];
	localPlayerUsernameOffset = config["localPlayerUsernameOffset"];
	killListStart = config["killListStart"];
	sendOnKill = config["sendOnKill"];
	onKillMsgsPath = config["onKillMsgsPath"];
	sendOnDeath = config["sendOnDeath"];
	onDeathMsgsPath = config["onDeathMsgsPath"];
	jumpAfterKillListOffset = config["jumpAfterKillListOffset"];
	DEBUG_MODE = config["DEBUG_MODE"];
	ifStream.close();

	std::ifstream readMeIf("trashtalk\\README.TXT");
	if (!readMeIf.good())
	{
		std::ofstream readMeOf("trashtalk\\README.txt");
		readMeOf << "By fl1k#2523\n\nHow to use formatting:\n%killer% -> replaces it with the killer\n%victim% -> replaces it with the victim\n\nif you want to be able to uninject set DEBUG_MODE to true in config.json, uninject key = VK_END (end)";
	}
	readMeIf.close();
}
