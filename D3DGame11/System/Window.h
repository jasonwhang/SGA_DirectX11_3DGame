#pragma once

// final을 붙이면 이 클래스는 절대로 상속을 시키지 않겠다는 의미이다.
// explicit는 명백하게 일치되는 자료형이 들어오지 않으면 받아들이지 않겠다는 의미이다.

class Window final
{
public:
	Window();
	virtual ~Window();
	void Initialize();

private:
};