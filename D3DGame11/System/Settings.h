#pragma once

// 메모리 영역
// Code = Compile된 코드 영역이 들어간다. -> 프로그램이 종료될 때까지 살아있다.
// Data = 전역 변수, 정적 변수 -> 프로그램이 종료될 때까지 살아있다.
// Stack = 지역 변수, 함수의 매개변수, 함수의 반환값 -> 함수가 종료될 때 사라진다.(;를 만나면)
// Heap

class Settings
{
public:
	static Settings& Get()
	{
		// 정적 변수 : 만드는 순간 한 번만 생성이 된다.
		// static은 초기화를 해주지 않으면 기본값으로 0이 설정이 된다.
		// 아래의 변수는 정적 지역 변수이다. -> Data영역에 생성이 된다.
		static Settings instance;
		return instance;
	}

	// c에서는 *가 있다면 c++에서는 &가 있다.
	// wstring공간을 바로 내보내겠다는 의미이다.
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

	// 싱글턴이기때문에 외부에서 생성자는 접근 못하도록 막아야 한다.
private:
	// 생성과 동시에 초기화 하는 방식
	// int a = 10;
	// int a;
	// a = 10;
	// 생성자 초기화 방법 2가지
	// 초기화 목록 리스트
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