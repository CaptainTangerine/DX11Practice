#pragma once

class UWindow
{
public:
	UWindow()  = default;
	~UWindow() = default;

public:
	bool Initialize(HINSTANCE hInstance, int width, int height);
	void Release();

	HWND GetHWnd() const { return m_hWnd; }

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND      m_hWnd      = nullptr;
	HINSTANCE m_hInstance = nullptr;
	int       m_Width     = 0;
	int       m_Height    = 0;
};
