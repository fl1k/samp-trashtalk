#include "MessageHandler.h"
#include <fstream>

std::vector<std::string> MessageHandler::killMsgs;
std::vector<std::string> MessageHandler::deathMsgs;

void MessageHandler::Start()
{
	std::ifstream ifStream("trashtalk\\" + Config::onKillMsgsPath);
	if (!ifStream.good())
	{
		std::ofstream ofStream("trashtalk\\" + Config::onKillMsgsPath);
		ofStream << "%victim% so ez\nez %victim% shitter";
		if (Config::DEBUG_MODE)
			std::cout << Config::onKillMsgsPath << " generated successfully\n";
	}
	std::string str;
	while (std::getline(ifStream, str))
		killMsgs.push_back(str);
	if (Config::DEBUG_MODE)
		std::cout << Config::onKillMsgsPath << " loaded successfully\n";
	ifStream.close();

	ifStream.open("trashtalk\\" + Config::onDeathMsgsPath);
	if (!ifStream.good())
	{
		std::ofstream ofStream("trashtalk\\" + Config::onDeathMsgsPath);
		ofStream << "gg %killer%\nt %killer%";
		if (Config::DEBUG_MODE)
			std::cout << Config::onDeathMsgsPath << " generated successfully\n";
	}
	while (std::getline(ifStream, str))
		deathMsgs.push_back(str);
	if (Config::DEBUG_MODE)
		std::cout << Config::onDeathMsgsPath << " loaded successfully\n";

	ifStream.close();
}

std::string MessageHandler::GetRandomKillMsg()
{
	srand((unsigned)time(0));
	return killMsgs[rand() % killMsgs.size()];
}

std::string MessageHandler::GetRandomDeathMsg()
{
	srand((unsigned)time(0));
	return deathMsgs[rand() % deathMsgs.size()];
}

const char* MessageHandler::FormatMessage(std::string msg, Kill* kill)
{
	int tagStartPos = -1, tagEndPos = -1;
	for (int i = 0; i < msg.length(); i++)
	{
		if (msg[i] == '%' && tagStartPos != -1)
			tagEndPos = i;

		if (tagStartPos != -1 && tagEndPos != -1)
		{
			std::string flag = msg.substr(tagStartPos, tagEndPos - tagStartPos + 1);
			if (flag == "%killer%") // killer
			{
				msg = msg.substr(0, tagStartPos) + kill->killer + msg.substr(tagEndPos + 1);
				i = 0;
			}
			else if (flag == "%victim%") // victim
			{
				msg = msg.substr(0, tagStartPos) + kill->victim + msg.substr(tagEndPos + 1);
				i = 0;
			}
			/*else if (flag == "%time%") // use onDeath
			{

				time_t timeNow;
				time(&timeNow);

				msg = msg.substr(0, tagStartPos) + kill->killer + msg.substr(tagEndPos + 1);
				i = 0;
			}*/
		}
		if (msg[i] == '%')
		{
			tagStartPos = i;
			tagEndPos = -1;
		}
	}
	char* c = new char[msg.size() + 1];
	std::copy(msg.begin(), msg.end(), c);
	c[msg.size()] = '\0';
	return c;
}
void MessageHandler::HookEvent()
{
	Kill* lastKill = Samp::GetLastKill();
	const char* localUsername = Samp::GetLocalUsername();
	if (Config::DEBUG_MODE)
		std::cout << FormatMessage("[KillList Update] %killer% killed %victim%\n", lastKill);

	if (Config::sendOnKill)
		OnKill(lastKill, localUsername);
	if (Config::sendOnDeath)
		OnDeath(lastKill, localUsername);
}

void MessageHandler::OnKill(Kill* lastKill, const char* localUsername)
{
	if (strcmp(lastKill->killer, localUsername) == 0)
	{
		std::cout << "Event triggered. Sending a message, type = kill\n";
		Samp::Say(FormatMessage(GetRandomKillMsg(), lastKill));
	}
}

void MessageHandler::OnDeath(Kill* lastKill, const char* localUsername)
{
	if (strcmp(lastKill->victim, localUsername) == 0) 
	{
		std::cout << "Event triggered. Sending a message, type = death\n";
		Samp::Say(FormatMessage(GetRandomDeathMsg(), lastKill));
	}
}