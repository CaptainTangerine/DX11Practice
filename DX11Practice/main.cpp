#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "App.h"
#include "ShaderManager.h"

#ifdef _DEBUG
BOOL WINAPI ConsoleHandler(DWORD signal)
{
	if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT)
	{
		PostQuitMessage(0);
		Sleep(50); 
		return TRUE;
	}
	return FALSE;
}
#endif

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


#ifdef _DEBUG
	AllocConsole();      
	SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout); 
	freopen_s(&fp, "CONOUT$", "w", stderr); 
	freopen_s(&fp, "CONIN$", "r", stdin);   
#endif

	UApp app;
	UShaderManager::GetInstance().CreateInstance();

	if (!app.Initialize(hInstance))
		return -1;

	app.Run();
	app.Release();

	UShaderManager::GetInstance().DestroyInstance();
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();  // 콘솔 닫기 전에 수동 체크!
	fflush(stdout);
	fclose(stdout);
	fclose(stderr);
	fclose(stdin);
	FreeConsole();
#endif

	return 0;
}
