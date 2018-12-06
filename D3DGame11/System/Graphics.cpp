#include "stdafx.h"
#include "Graphics.h"

// �����ʹ� nullptr�� �ʱ�ȭ�� ������

Graphics::Graphics()
	: device(nullptr)
	, deviceContext(nullptr)
	, swapChain(nullptr)
	, rtv(nullptr)
	, dsv(nullptr)
	, clearColor(0xFF555566)
{
}

Graphics::~Graphics()
{
	// Initialize() �Լ� �ȿ� �ִ�
	// D3D11CreateDeviceAndSwapChain -> ���� ������ ���� ���߿� �����ؾ� �Ѵ�.(����ȭ����)
	SAFE_RELEASE(dsv);
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
	SAFE_RELEASE(swapChain);
}

void Graphics::Initialize()
{
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = static_cast<uint>(Settings::Get().GetWidth());
	bufferDesc.Height = static_cast<uint>(Settings::Get().GetHeight());

	// ���߿� fullscreenMode�� �� �� ������ �����ش�.
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;

	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// UNSPECIFIED : ��Ȯ�� -> �������� �ʾҴٰ� �˷��ִ� ��(�Ʒ� �ΰ��� ���������� �ʾƵ� �Ǳ��ϴ�)
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	// SampleDesc = ���ø��� �� �������� ���� �����̴�.
	swapChainDesc.SampleDesc.Count = 1;
	// ��� ������ �������� �� ������(0��� ���� �⺻���� ���ڴٴ� �ǹ��̴�.) => �ؽ��ĸ� �� �� �ٽ� �������ֽŴ�.
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = Settings::Get().GetHandle();
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		//D3D_FEATURE_LEVEL_11_1, // �� ������ �п� ��ǻ�Ϳ��� ������ ���� �ʴ´�.
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	//DXGI => DirectX Graphic Interface
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain, // ���������Ͱ� ����. -> ���������͸� ���� ���� : 
		&device,
		nullptr,
		&deviceContext
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

}

// �׸��� �۾��� �����ϴ� �Լ�
void Graphics::BeginScene()
{
	deviceContext->OMSetRenderTargets
	(
		1,
		&rtv,
		dsv
	);
	deviceContext->ClearRenderTargetView
	(
		rtv,
		clearColor
	);
}

void Graphics::EndScene()
{
	// Present -> �����ִ�(Presentation) -> ����ۿ��� �׷��� ������ swap���� ������ ���� �����ִ� �Լ�
	HRESULT hr = swapChain->Present
	(
		1,		// SyncInterval -> ���� ����ȭ(Settings->bvSync(true))
		0		// Flags
	);
	// SUCCEEDED : ���������� true�� ���´�.
	assert(SUCCEEDED(hr));
}

void Graphics::CreateBackBuffer(const uint & width, const uint & height)
{
	HRESULT hr = swapChain->ResizeBuffers
	(
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN,
		0
	);
	assert(SUCCEEDED(hr));

	// ID3D11Texture2D -> ���� ������
	ID3D11Texture2D* backBuffer = nullptr;
	hr = swapChain->GetBuffer
	(
		0, // ���� ù��°���� ����Ѵ�.
		__uuidof(ID3D11Texture2D), // Interface ID
		reinterpret_cast<void**>(&backBuffer) // void** �ڷ����� ���� �Ѵ�.(ĳ�������� ����ȯ�� ���ش�.)
	);
	assert(SUCCEEDED(hr));

	// RenderTarget -> ��ȭ�� -> ��ȭ���� ����� �۾�
	// device�� ���ؼ� �������� ���������.
	// rtv -> ��ǻ�Ͱ� �����ϱ� ���� �������� �� ������
	// backBuffer->���������͸� rtv�� ���������ش�.
	hr = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
	assert(SUCCEEDED(hr));

	// ���������ο� ���������͸� �־��ִ� �۾��� �Ѵ�.
	deviceContext->OMSetRenderTargets
	(
		1, // 8������ ��밡��
		&rtv,
		dsv
	);

	// Create Viewport(���̴� ����) -> ��𿡼� ������ ���̰� �� ������ ����
	viewport.TopLeftX = 0;		// �»�� ���� width���� �׷����� �Ѵ�.
	viewport.TopLeftY = 0;		// �»�� ���� height���� �׷����� �Ѵ�.
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// ������ viewport�� ���������ο� �־��ش�.
	deviceContext->RSSetViewports
	(
		1,
		&viewport // viewPort�� ������(�ּ�)
	);
}
