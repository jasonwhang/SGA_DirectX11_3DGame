#pragma once


class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

private:
	// COM Interface -> I : 1) Create��� �Լ��� �����Ѵ�. 2) Release��� �Լ��� �����Ѵ�. 3)DESC(Discription)
	// ����� �ų� �����ϴ� ���� device�� �Ѵ�.
	ID3D11Device* device;
	// Context = ���� -> 10���� Device�� deviceContext�� ���ҽ��״�.
	// �׸��� ���� deviceContext���� �Ѵ�.(pipeline)
	ID3D11DeviceContext* deviceContext;
	// ������۸��� ���ֱ� ���� �����̴�.
	IDXGISwapChain* swapChain;
	// View�� �������� �ؽ��Ķ�� �����ϸ� �ȴ�.
	// 1)Render Target View(�׷����� ����)
	// -> �ѹ��� 8�������� �ؽ��ĸ� �׸� �� �ִ�.
	// 2) Depth View 
	// 3) ShaderRenderView
	ID3D11RenderTargetView* rtv;
};