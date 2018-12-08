#pragma once
#include "../Subsystem/ISubsystem.h"

class Graphics : public ISubsystem
{
public:
	Graphics(class Context* context);
	virtual ~Graphics();

	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	void Initialize() override;
	void Update() override {}

	void ResizeClient(const uint& width, const uint& height);
	void BeginScene();
	void EndScene();

private:
	ID3D11Device * device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;

	ID3D11Debug* debugDevice;
	uint gpuMemorySize;
	wstring gpuDescription;
	uint numerator;
	uint denominator;

	D3DXCOLOR clearColor;
	ID3D11DepthStencilView* depthStencilView; // 깊이(3D이기 때문에 필요한 변수이다.)
	ID3D11RenderTargetView* renderTargetView; // 도화지
	D3D11_VIEWPORT viewport;
};