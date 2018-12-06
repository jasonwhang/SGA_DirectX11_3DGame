#include "stdafx.h"
#include "Window.h"

// CALLBACK은 시스템이 호출한다.

LRESULT CALLBACK WndProc
(
	HWND handle,
	// uint는 stdafx.h에서 사용자 매크로 위에 재정의하였다.
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
	// (HBRUSH)는 c언어 방식의 캐스팅 방법이다.
	// static_cast는 c++ 방식의 캐스팅 방법이다.
	// c++에는 4가지의 캐스팅 방법이 있다.
	// static_cast - 논리적인 형변환을 할 때
	// const_cast - 상수로 선언된 것을 날 릴 수 있다.
	// dynamic_cast - 부모자식관계, 가상함수가 있어야 한다. 
	// reinterpret_cast - () c언어와 같은 방식이다.
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
	// (TODO) : Settings 만들고 처리 메뉴창에 보기를 누르고 작업목록을 누르면 나중에 만들어야 할 목록들이 나온다.
	wndClass.hInstance = Settings::Get().GetHInstance();
	wndClass.lpfnWndProc = static_cast<WNDPROC>(WndProc);
	wndClass.lpszClassName = Settings::Get().GetAppName().c_str();
	wndClass.lpszMenuName = nullptr;
	// Horizantal : 수평 -> 수평으로 움직일 때 다시 그려랴
	// Vertical : 수직 -> 수직으로 움직을 때 다시 그려라
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD check = RegisterClassEx(&wndClass);
	// 0과 같아야 등록이 되었다
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
	// hwnd가 null인 경우 만들어지지 않았으므로 assert에서 걸려야 한다.
	assert(hwnd != nullptr);
	Settings::Get().SetHandle(hwnd);

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
}
