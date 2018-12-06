#pragma once


class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	// 외부에서도 사용할 수 있게 해주아야 한다.(파이프라인은 아직 많이 남았다)
	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	void Initialize();

	void BeginScene();
	void EndScene();

private:
	void CreateBackBuffer(const uint& width, const uint& height);

private:
	// COM Interface -> I : 1) Create라는 함수로 생성한다. 2) Release라는 함수로 삭제한다. 3)DESC(Discription)
	// 만드는 거나 생성하는 것은 device가 한다.
	ID3D11Device * device;
	// Context = 내용 -> 10부터 Device와 deviceContext를 분할시켰다.
	// 그리는 것은 deviceContext에서 한다.(pipeline)
	ID3D11DeviceContext* deviceContext;
	// 더블버퍼링을 해주기 위한 변수이다.
	IDXGISwapChain* swapChain;

	// View가 붙어있으면 텍스쳐이다.
	ID3D11RenderTargetView* rtv;
	// 깊이만 저장하는 텍스쳐를 따로 만든 저장소이다.
	ID3D11DepthStencilView* dsv;
	D3D11_VIEWPORT viewport;
	// 지울 색 -> 전체를 지운다음에 다시 그려주는 것이 컴퓨터는 더 빠르다.
	// FLOAT r, FLOAT g, FLOAT b, FLOAT a -> DX에서는 0부터 1까지이다(API에서는 0부터 255까지이다.)
	// DX에서는 1을 준다는 것은 API에서 255가 되는 것이다.
	D3DXCOLOR clearColor;
};