Installation / Setup:
1. Download the dll
2. Inject the dll into the gta_sa.exe process
3. Exit the game, go to your gta folder, in it a folder called trashtalk should appear. In it you will find config.json, onKillMsgs.txt, onDeathMsgs.txt and README.txt with formatting instructions. There will be 2 default messages in both text files.
*) If you want to be able to uninject mid playing enable DEBUG_MODE in config and uninject using the END key (VK_END)

Features:
- Send a formatted message when you kill somebody (onKill) - Enabled by default, can be disabled in config.json
- Send a formatted message when you die (onDeath) - Disabled by default, can be enabled in config.json

Requirements:
- SA:MP 0.3.7 R1 (at some point I'll update it to not get offsets manually from the config file and instead find patterns in memory)
- A server with a kill list enabled(it hooks to the kill list)
- A working DLL injector 
