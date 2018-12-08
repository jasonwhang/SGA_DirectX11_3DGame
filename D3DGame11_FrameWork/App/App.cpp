#include "stdafx.h"
#include "App.h"
#include "../FrameWork/Core/Window.h"

App::App()
{
	window = new Window();
	window->Initialize();

	context = new Context();
	context->RegistSubsystem(new Graphics(context));
}

App::~App()
{
	// ���� ������ ���� ���߿� ����������
	SAFE_DELETE(context);
	SAFE_DELETE(window);
}

WPARAM App::Run()
{
	// ����ü �ʱ�ȭ 2���� ���
	// 1)MSG msg = { 0 }; -> ����ü ���� �������� ���� 0���� �ʱ�ȭ�� ������ �������� ���� �� �ִ�.
	// ����ü ���ο� �����Ͱ� ������ ��쿡 �ʱ�ȭ�� ���� ���� �� �ִ�. 
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	auto graphics = context->GetSubsystem<Graphics>();

	// �ʱ�ȭ
	Initialize();

	while (true)
	{
		// GetMessage�� �޽����� ���� ������ ���
		// PeekMessage�� �޽����� ������ ������ ��������.
		// PM_REMOVE�� �޽����� �� ó���Ǹ� �����ϵ��� �ϴ� ��ũ��
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// �� �ȿ����� �޽����� ������ ����� ó�� ����̴�.

			if (msg.message == WM_QUIT)
				break;

			// C���� ������ �Էµ� �޽����� �������ش�.
			TranslateMessage(&msg);
			// WndProc CallBack�Լ����� �޽����� �Ѱ��ش�.
			DispatchMessage(&msg);
		}
		else
		{
			// �޽����� ������ �ʾ��� ��쿡 ó���Ǵ� �κ��̴�.

			Update();

			// ������۸� �ϼ�
			graphics->BeginScene();
			{
				Render(); // ����ۿ� �׷��� ������ �׷��ش�.
			}
			graphics->EndScene(); // ����ۿ� �׷��� ������ ������ �����ش�.
		}
	}

	// �޸� ����
	Destory();

	return msg.wParam;
}
