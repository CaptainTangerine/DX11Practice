#include "pch.h"
#include "App.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"

bool UApp::Initialize(HINSTANCE hInstance)
{
	Window = std::make_unique<UWindow>();
	if (!Window->Initialize(hInstance, 1280, 720))
		return false;

	Input = std::make_unique<UInput>();
	if(!Input->Initalize())
	return true;
}

void UApp::Run()
{
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//input
		
		//GameLogic
		
		//Render

	}
}

void UApp::Release()
{

	if (Window)
	{
		Window->Release();
		Window.reset();
	}

}
