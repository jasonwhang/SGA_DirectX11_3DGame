#pragma once


class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	// �ܺο����� ����� �� �ְ� ���־ƾ� �Ѵ�.(������������ ���� ���� ���Ҵ�)
	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	void Initialize();

	void BeginScene();
	void EndScene();

private:
	void CreateBackBuffer(const uint& width, const uint& height);

private:
	// COM Interface -> I : 1) Create��� �Լ��� �����Ѵ�. 2) Release��� �Լ��� �����Ѵ�. 3)DESC(Discription)
	// ����� �ų� �����ϴ� ���� device�� �Ѵ�.
	ID3D11Device * device;
	// Context = ���� -> 10���� Device�� deviceContext�� ���ҽ��״�.
	// �׸��� ���� deviceContext���� �Ѵ�.(pipeline)
	ID3D11DeviceContext* deviceContext;
	// ������۸��� ���ֱ� ���� �����̴�.
	IDXGISwapChain* swapChain;

	// View�� �پ������� �ؽ����̴�.
	ID3D11RenderTargetView* rtv;
	// ���̸� �����ϴ� �ؽ��ĸ� ���� ���� ������̴�.
	ID3D11DepthStencilView* dsv;
	D3D11_VIEWPORT viewport;
	// ���� �� -> ��ü�� ��������� �ٽ� �׷��ִ� ���� ��ǻ�ʹ� �� ������.
	// FLOAT r, FLOAT g, FLOAT b, FLOAT a -> DX������ 0���� 1�����̴�(API������ 0���� 255�����̴�.)
	// DX������ 1�� �شٴ� ���� API���� 255�� �Ǵ� ���̴�.
	D3DXCOLOR clearColor;
};