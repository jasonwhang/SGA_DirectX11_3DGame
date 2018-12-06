#include "stdafx.h"
#include "Window.h"

// CALLBACK�� �ý����� ȣ���Ѵ�.

LRESULT CALLBACK WndProc
(
	HWND handle,
	// uint�� stdafx.h���� ����� ��ũ�� ���� �������Ͽ���.
	uint message,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (message)
	{
	case WM_CLOSE:
	case WM_KEYDOWN:
		switch (wParam)
			case VK_ESCAPE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(handle, message, wParam, lParam);
	}

	return 0;
}

Window::Window()
{
}

Window::~Window()
{
	DestroyWindow(Settings::Get().GetHandle());
	UnregisterClass(Settings::Get().GetAppName().c_str(), Settings::Get().GetHInstance());
}

void Window::Initialize()
{
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	// (HBRUSH)�� c��� ����� ĳ���� ����̴�.
	// static_cast�� c++ ����� ĳ���� ����̴�.
	// c++���� 4������ ĳ���� ����� �ִ�.
	// static_cast - ������ ����ȯ�� �� ��
	// const_cast - ����� ����� ���� �� �� �� �ִ�.
	// dynamic_cast - �θ��ڽİ���, �����Լ��� �־�� �Ѵ�. 
	// reinterpret_cast - () c���� ���� ����̴�.
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
	// (TODO) : Settings ����� ó�� �޴�â�� ���⸦ ������ �۾������ ������ ���߿� ������ �� ��ϵ��� ���´�.
	wndClass.hInstance = Settings::Get().GetHInstance();
	wndClass.lpfnWndProc = static_cast<WNDPROC>(WndProc);
	wndClass.lpszClassName = Settings::Get().GetAppName().c_str();
	wndClass.lpszMenuName = nullptr;
	// Horizantal : ���� -> �������� ������ �� �ٽ� �׷���
	// Vertical : ���� -> �������� ������ �� �ٽ� �׷���
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD check = RegisterClassEx(&wndClass);
	// 0�� ���ƾ� ����� �Ǿ���
	assert(check != 0);

	HWND hwnd = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		Settings::Get().GetAppName().c_str(),
		Settings::Get().GetAppName().c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<int>(Settings::Get().GetWidth()),
		static_cast<int>(Settings::Get().GetHeight()),
		nullptr,
		nullptr,
		Settings::Get().GetHInstance(),
		nullptr
	);
	// hwnd�� null�� ��� ��������� �ʾ����Ƿ� assert���� �ɷ��� �Ѵ�.
	assert(hwnd != nullptr);
	Settings::Get().SetHandle(hwnd);

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
}
