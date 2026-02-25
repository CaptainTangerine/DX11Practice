#include "pch.h"
#include "Window.h"

bool UWindow::Initialize(HINSTANCE hInstance, int width, int height)
{
	m_hInstance = hInstance;
	m_Width     = width;
	m_Height    = height;

	WNDCLASSW wc      = {};
	wc.lpfnWndProc   = WndProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = L"JungleWindowClass";

	if (!RegisterClassW(&wc))
		return false;

	m_hWnd = CreateWindowW(
		L"JungleWindowClass",
		L"Game Tech Lab",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		nullptr, nullptr, hInstance, nullptr
	);

	if (!m_hWnd)
		return false;

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}

void UWindow::Release()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
}

LRESULT CALLBACK UWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
