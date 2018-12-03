#pragma once


class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	void Initialize();

	void BeginScene();
	void EndScene();

private:
	void CreateBackBuffer(const uint& width, const uint& height);

private:
	ID3D11Device * device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;

	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;
	D3D11_VIEWPORT viewport;
	D3DXCOLOR clearColor;
};