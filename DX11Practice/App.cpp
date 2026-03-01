#include "pch.h"
#include "App.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Graphics.h"
#include "ShaderManager.h"
#include "LevelManager.h"


UApp::UApp()
{
}

UApp::~UApp()
{

}

bool UApp::Initialize(HINSTANCE hInstance)
{
	UInput::GetInstance().Initialize();

	Window = std::make_unique<UWindow>();
	if (!Window->Initialize(hInstance, 1280, 720))
	{
		return false;
	}

	Graphics = std::make_unique<UGraphics>();
	Graphics->Initialize(Window->GetHWnd());
	
	Renderer = std::make_unique<URenderer>(Graphics->GetDevice(), Graphics->GetDeviceContext(), Graphics->GetSwapChain());
	Renderer->Initialize();
	
	LevelManager = std::make_unique<ULevelManager>();
	LevelManager->ChangeLevel(*Graphics->GetDevice());

	UShaderManager::GetInstance().CompileShaderFile(*Graphics->GetDevice(),
		TEXT("ShaderSimple.hlsl"), EShaderType::Simple, FVertexSimple::Elements, FVertexSimple::ElementNum);

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

			Renderer->BeginScene();
			Renderer->Render(*LevelManager->GetCurrentLevel());
			Renderer->EndScene();

		}
		else
		{
			Sleep(0);
		}

	}
}

void UApp::Release()
{
	UShaderManager::GetInstance().CleanUp();

	if (LevelManager)
	{
		LevelManager->Release();
		LevelManager.reset();
	}
	if (Renderer)
	{
		Renderer->Release();
		Renderer.reset();
	}
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
}
