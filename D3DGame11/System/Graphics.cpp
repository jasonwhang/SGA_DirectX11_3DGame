#include "stdafx.h"
#include "Graphics.h"

// 포인터는 nullptr로 초기화를 해주자

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
	// Initialize() 함수 안에 있는
	// D3D11CreateDeviceAndSwapChain -> 먼저 생성한 것을 나중에 삭제해야 한다.(습관화하자)
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

	// 나중에 fullscreenMode를 할 때 개념을 집어준다.
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;

	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// UNSPECIFIED : 미확인 -> 정리되지 않았다고 알려주는 것(아래 두개는 설정해주지 않아도 되긴하다)
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	// SampleDesc = 샘플링을 할 것인지에 대한 설정이다.
	swapChainDesc.SampleDesc.Count = 1;
	// 어느 정도의 수준으로 할 것인지(0라는 것은 기본값을 쓰겠다는 의미이다.) => 텍스쳐를 할 때 다시 정리해주신다.
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = Settings::Get().GetHandle();
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		//D3D_FEATURE_LEVEL_11_1, // 이 버전은 학원 컴퓨터에서 지원이 되지 않는다.
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
		&swapChain, // 이중포인터가 들어간다. -> 이중포인터를 쓰는 이유 : 
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

// 그리는 작업을 시작하는 함수
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
	// Present -> 보여주다(Presentation) -> 백버퍼에서 그려준 내용을 swap시켜 앞으로 나와 보여주는 함수
	HRESULT hr = swapChain->Present
	(
		1,		// SyncInterval -> 수직 동기화(Settings->bvSync(true))
		0		// Flags
	);
	// SUCCEEDED : 성공했으면 true가 나온다.
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

	// ID3D11Texture2D -> 원본 데이터
	ID3D11Texture2D* backBuffer = nullptr;
	hr = swapChain->GetBuffer
	(
		0, // 제일 첫번째것을 사용한다.
		__uuidof(ID3D11Texture2D), // Interface ID
		reinterpret_cast<void**>(&backBuffer) // void** 자료형이 들어가야 한다.(캐스팅으로 형변환을 해준다.)
	);
	assert(SUCCEEDED(hr));

	// RenderTarget -> 도화지 -> 도화지를 만드는 작업
	// device를 통해서 번역본이 만들어진다.
	// rtv -> 컴퓨터가 이해하기 쉽게 번역시켜 줄 번역본
	// backBuffer->원본데이터를 rtv로 번역시켜준다.
	hr = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
	assert(SUCCEEDED(hr));

	// 파이프라인에 원본데이터를 넣어주는 작업을 한다.
	deviceContext->OMSetRenderTargets
	(
		1, // 8개까지 사용가능
		&rtv,
		dsv
	);

	// Create Viewport(보이는 영역) -> 어디에서 어디까지 보이게 할 것인지 설정
	viewport.TopLeftX = 0;		// 좌상단 부터 width까지 그려지게 한다.
	viewport.TopLeftY = 0;		// 좌상단 부터 height까지 그려지게 한다.
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// 설정한 viewport를 파이프라인에 넣어준다.
	deviceContext->RSSetViewports
	(
		1,
		&viewport // viewPort의 포인터(주소)
	);
}
