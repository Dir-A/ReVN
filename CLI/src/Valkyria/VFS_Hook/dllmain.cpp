#include <Windows.h>

#include <Rut/RxCmd.h>
#include <RxHook/API.h>
#include <Valkyria/VFS_Hook.h>


static DWORD g_dwExeBase = (DWORD)GetModuleHandleW(NULL);


void StartHook()
{
	Rut::RxCmd::Alloc(L"Valkyria_FileHook");

	// プレイ！プレイ！プレイ！ロック！ PKG
	Valkyria::VFS::HookScriptRead(0x0041DA10, true);
	Valkyria::VFS::HookMediasRead(0x0041D770, true);
	Rut::RxHook::HookCreateFontIndirectA(0x86, "SimHei");
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		StartHook();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void __declspec(dllexport) DirA() {};