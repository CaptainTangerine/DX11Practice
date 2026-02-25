#pragma once

class UInput;
class UWindow;
class URenderer;

class UApp
{
public:
	UApp()  = default;
	~UApp() = default;

public:
	bool Initialize(HINSTANCE hInstance);
	void Run();
	void Release();

private:
	std::unique_ptr<UInput>	   Input;
	std::unique_ptr<UWindow>   Window;
	std::unique_ptr<URenderer> Renderer;


};
