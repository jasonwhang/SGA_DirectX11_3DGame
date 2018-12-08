#pragma once

// App은 부모클래스이다(Game이 자식클래스)

class App
{
public:
	App();
	virtual ~App();

	virtual WPARAM Run();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destory() = 0;

protected:
	class Window* window;
	class Context* context;
};