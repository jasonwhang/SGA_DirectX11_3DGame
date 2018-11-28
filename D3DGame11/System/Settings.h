#pragma once

// �޸� ����
// Code = Compile�� �ڵ� ������ ����. -> ���α׷��� ����� ������ ����ִ�.
// Data = ���� ����, ���� ���� -> ���α׷��� ����� ������ ����ִ�.
// Stack = ���� ����, �Լ��� �Ű�����, �Լ��� ��ȯ�� -> �Լ��� ����� �� �������.(;�� ������)
// Heap

class Settings
{
public:
	static Settings& Get()
	{
		// ���� ���� : ����� ���� �� ���� ������ �ȴ�.
		// static�� �ʱ�ȭ�� ������ ������ �⺻������ 0�� ������ �ȴ�.
		// �Ʒ��� ������ ���� ���� �����̴�. -> Data������ ������ �ȴ�.
		static Settings instance;
		return instance;
	}

	// c������ *�� �ִٸ� c++������ &�� �ִ�.
	// wstring������ �ٷ� �������ڴٴ� �ǹ��̴�.
	const wstring& GetAppName() const { return appName; }
	HINSTANCE GetHInstance() const { return hInstance; }
	HWND GetHandle() const { return handle; }
	const float& GetWidth() const { return width; }
	const float& GetHeight() const { return height; }

	void SetAppName(const wstring& appName) { this->appName = appName; }
	void SetHInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }
	void SetHandle(HWND handle) { this->handle = handle; }
	void SetWidth(const float& width) { this->width = width; }
	void SetHeight(const float& height ) { this->height = height; }

	// �̱����̱⶧���� �ܺο��� �����ڴ� ���� ���ϵ��� ���ƾ� �Ѵ�.
private:
	// ������ ���ÿ� �ʱ�ȭ �ϴ� ���
	// int a = 10;
	// int a;
	// a = 10;
	// ������ �ʱ�ȭ ��� 2����
	// �ʱ�ȭ ��� ����Ʈ
	Settings() 
		:appName(L""),
		hInstance(nullptr),
		handle(nullptr),
		width(1280),
		height(720),
		bVSync(true),
		bFullScreen(false)
	{
		// this->appName = L" "
	}

private:
	wstring appName;
	HINSTANCE hInstance;
	HWND handle;
	float width;
	float height;
	bool bVSync;
	bool bFullScreen;
};