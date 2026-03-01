#pragma once

class UInput;
class UWindow;
class URenderer;
class UGraphics;
class ULevelManager;

class UApp
{
public:
	UApp();
	~UApp();

public:
	bool Initialize(HINSTANCE hInstance);
	void Run();
	void Release();

private:
	const int				   TargetFrame = { 60 };
	float					   DeltaTime   = { 1.f / TargetFrame };

	std::unique_ptr<UWindow>   Window;

	std::unique_ptr<UGraphics> Graphics;
	std::unique_ptr<URenderer> Renderer;
	std::unique_ptr<ULevelManager> LevelManager;

};
