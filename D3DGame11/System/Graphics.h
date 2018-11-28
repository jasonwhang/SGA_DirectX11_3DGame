#pragma once


class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

private:
	// COM Interface -> I : 1) Create라는 함수로 생성한다. 2) Release라는 함수로 삭제한다. 3)DESC(Discription)
	// 만드는 거나 생성하는 것은 device가 한다.
	ID3D11Device* device;
	// Context = 내용 -> 10부터 Device와 deviceContext를 분할시켰다.
	// 그리는 것은 deviceContext에서 한다.(pipeline)
	ID3D11DeviceContext* deviceContext;
	// 더블버퍼링을 해주기 위한 변수이다.
	IDXGISwapChain* swapChain;
	// View가 붙은것은 텍스쳐라고 생각하면 된다.
	// 1)Render Target View(그려지는 영역)
	// -> 한번에 8개까지의 텍스쳐를 그릴 수 있다.
	// 2) Depth View 
	// 3) ShaderRenderView
	ID3D11RenderTargetView* rtv;
};