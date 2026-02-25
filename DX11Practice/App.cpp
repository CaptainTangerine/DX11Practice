#include "pch.h"
#include "App.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Graphics.h"

bool UApp::Initialize(HINSTANCE hInstance)
{
	Window = std::make_unique<UWindow>();
	if (!Window->Initialize(hInstance, 1280, 720))
	{
		return false;
	}

	Input = std::make_unique<UInput>();
	if (!Input->Initialize())
	{
		return false;
	}

	Graphics = std::make_unique<UGraphics>();
	Graphics->Initialize(Window->GetHWnd());

	return true;
}

void UApp::Run()
{
	MSG msg = {};

	LARGE_INTEGER StartTime, EndTime, Frequency;

	double		  TargetFrameMilliSecond = 1.f / TargetFrame * 1000.f;
	double		  ElaspedMilliSecond = 0.f;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartTime);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		QueryPerformanceCounter(&EndTime);
		double CounterInterval = static_cast<double>(EndTime.QuadPart - StartTime.QuadPart);
		ElaspedMilliSecond = CounterInterval / Frequency.QuadPart * 1000.f;

		if (ElaspedMilliSecond >= TargetFrameMilliSecond)
		{
			StartTime = EndTime;
			DeltaTime = static_cast<float>(ElaspedMilliSecond / 1000.f); // 초단위로

			//input
			UInput::GetInstance().Update();
			//GameLogic

			//Render
			Graphics->BeginScene();

			Graphics->EndScene();

		}
		else
		{
			Sleep(0);
		}

	}
}

void UApp::Release()
{

	if (Graphics)
	{
		Graphics->Release();
		Graphics.reset();
	}

	if (Window)
	{
		Window->Release();
		Window.reset();
	}

	if (Input)
	{
		Input->Release();
		Input.reset();
	}
}
