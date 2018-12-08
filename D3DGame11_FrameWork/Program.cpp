#include "stdafx.h"
#include "./App/Game.h"

int WINAPI WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmpParam,
	int nCmdShow
)
{
	Settings::Get().SetAppName(L"D3D11Game");
	Settings::Get().SetWindowInstance(hInstance);
	Settings::Get().SetWidth(1280);
	Settings::Get().SetHeight(720);
	Settings::Get().SetIsVsync(true); // 수직동기화
	Settings::Get().SetIsFullScreen(false);

	Game* game = new Game();

	WPARAM wParam = game->Run();

	SAFE_DELETE(game);
	return wParam;
}