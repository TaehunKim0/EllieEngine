#include "PreCompiled.h"
#include "WindowsApp.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ScreenPoint ScreenSize(960, 600);
	if (!WindowsApp::Create(hInstance, ScreenSize))
	{
		return -1;
	}

	WindowsApp::Show(WindowsApp::g_Handle);
	
	while (WindowsApp::Tick())
	{
		//¼ÒÇÁÆ®¿þ¾î ·»´õ·¯ Æ½
	}

	WindowsApp::Destroy();
	return 0;
}