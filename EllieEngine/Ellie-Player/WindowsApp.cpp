
#include "WindowsApp.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ScreenPoint ScreenSize(960, 600);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (!WindowsApp::Create(hInstance, ScreenSize))
	{
		return -1;
	}

	WindowsApp::Show(WindowsApp::g_Handle);
	WindowsApp::Tick();

	WindowsApp::Destroy();
	return 0;
}