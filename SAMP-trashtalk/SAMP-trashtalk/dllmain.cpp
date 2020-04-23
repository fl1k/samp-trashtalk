#define WIN32_LEAN_AND_MEAN   
#include <iostream>
#include <windows.h>
#include "Hook.h"
#include "structs.h"
#include <string>
#include "Config.h"
#include "MessageHandler.h"

#define DEBUG_ENABLED true;

DWORD jmpBackAddress;
DWORD tempA;

__declspec (naked) void HookFunc()
{
	__asm
	{
		pushad
	}
	MessageHandler::HookEvent();
	__asm
	{
		popad
		jmp tempA
		jmp[jmpBackAddress]
	}
}

DWORD WINAPI HSEntry(HMODULE hModule)
{
	Config::Load();
	FILE* f = nullptr;
	if (Config::DEBUG_MODE)
	{
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);
		std::cout << "DEBUG_ENABLED is true, running console..\n";
		std::cout << "Injecting...\n";
	}
	MessageHandler::Start();
	uintptr_t sampModuleAddr = (uintptr_t)GetModuleHandle("samp.dll");
	uintptr_t addressToHook = sampModuleAddr + Config::updateKillListFuncOffset;
	jmpBackAddress = addressToHook + 0x5;
	Hook hook((BYTE*)addressToHook, (BYTE*)HookFunc, 0x5);

	Samp::sampModuleAddr = sampModuleAddr;
	Samp::killListStart = Config::killListStart;
	Samp::sayFuncOffset = Config::sayFuncOffset;
	Samp::addToChatFuncOffset = Config::addToChatFuncOffset;
	Samp::localPlayerUsernameOffset = Config::localPlayerUsernameOffset;

	tempA = sampModuleAddr + Config::jumpAfterKillListOffset;
	bool hooked = hook.Place();

	if (Config::DEBUG_MODE)
		if (hooked)
			std::cout << "Hooked successfuly\n";

	while (true)
	{
		//system("cls");
		if (Config::DEBUG_MODE)
			if (GetAsyncKeyState(VK_END))
				break;
		//Kill* lastKill = (Kill*)((*(uintptr_t*)(sampModuleAddr + 0x0021A0EC)) + 0x4);
		//Kill* kl = (lastKill + 4);
		//Kill* kl = Samp::GetLastKill();
		//std::cout << kl->killer << " -> " << kl->killed << '\n';
		Sleep(200);
	}
	bool undoHook = hook.Undo();
	if (Config::DEBUG_MODE)
		if (undoHook)
			std::cout << "Unhooked successfuly\n";

	Sleep(1000);
	if (Config::DEBUG_MODE)
	{
		std::cout << "Uninjecting..\n";
		Sleep(1000);
		fclose(f);
		FreeConsole();
	}
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HSEntry, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
