#include "stdafx.h"
#include "App.h"
#include "../System/Window.h"

App::App()
{
	window = new Window();
	window->Initialize();
}

App::~App()
{
}

WPARAM App::Run()
{
	// 구조체 초기화 2가지 방법
	// 1)MSG msg = { 0 }; -> 구조체 안의 변수들이 전부 0으로 초기화가 되지만 문제점이 생길 수 있다.
	// 구조체 내부에 포인터가 들어가있을 경우에 초기화가 되지 않을 수 있다. 
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// 초기화
	Initialize();

	while (true)
	{
		// GetMessage는 메시지가 들어올 때까지 대기
		// PeekMessage는 메시지가 들어오지 않으면 지나간다.
		// PM_REMOVE는 메시지가 다 처리되면 제거하도록 하는 매크로
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 이 안에서는 메시지가 들어왔을 경우의 처리 방법이다.

			if (msg.message == WM_QUIT)
				break;

			// C언어같은 것으로 입력된 메시지를 번역해준다.
			TranslateMessage(&msg);
			// WndProc CallBack함수에게 메시지를 넘겨준다.
			DispatchMessage(&msg);
		}
		else
		{
			// 메시지가 들어오지 않았을 경우에 처리되는 부분이다.

			Update();
			Render();
		}
	}

	// 메모리 삭제
	Destory();

	return msg.wParam;
}
