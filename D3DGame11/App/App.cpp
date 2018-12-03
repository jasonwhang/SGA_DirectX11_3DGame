#include "stdafx.h"
#include "App.h"
#include "../System/Window.h"
#include "../System/Graphics.h"

App::App()
{
	window = new Window();
	window->Initialize();

	graphics = new Graphics;
	graphics->Initialize();
}

App::~App()
{
	SAFE_DELETE(graphics);
	SAFE_DELETE(window);
}

WPARAM App::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	Initialize();

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();

			graphics->BeginScene();
			{
				Render();
			}
			graphics->EndScene();
		}
	}

	Destory();

	return msg.wParam;
}
