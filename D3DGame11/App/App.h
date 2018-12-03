#pragma once

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
	class Graphics* graphics;
};