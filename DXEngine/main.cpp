#include "pch.h"

#include <Windows.h>
#include "EngineCore.h"
#include "EngineWindow.h"
#include <crtdbg.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(244);
#endif

	(hPrevInstance);
	(lpCmdLine);
	(nCmdShow);

	EngineCore Engine(hInstance);

	EngineWindow* NewWindow = EngineWindow::CreateEngineWindow(L"Test0");
	NewWindow->Show();
	NewWindow = EngineWindow::CreateEngineWindow(L"Test1");
	NewWindow->Show();
	NewWindow = EngineWindow::CreateEngineWindow(L"Test2");
	NewWindow->Show();


	Engine.EngineLoop();

	return 0;
}