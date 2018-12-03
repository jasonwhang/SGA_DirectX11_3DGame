#include "stdafx.h"
#include "Game.h"

void Game::Initialize()
{
	// Create Vertex Data(원본데이터)
	vertices = new VertexColor[6];

	vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // 0
	vertices[0].color = D3DXCOLOR(1, 0, 0, 1);

	vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); //1
	vertices[1].color = D3DXCOLOR(0, 1, 0, 1);

	vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); //2
	vertices[2].color = D3DXCOLOR(0, 0, 1, 1);

	vertices[3].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); //2
	vertices[3].color = D3DXCOLOR(1, 1, 0, 1);

	vertices[4].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); //1
	vertices[4].color = D3DXCOLOR(0, 1, 1, 1);

	vertices[5].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); //3
	vertices[5].color = D3DXCOLOR(1, 0, 1, 1);

	// Create VertexBuffer(번역본)
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexColor) * 6;

	// 실질적으로 원본데이터의 정보가 들어가는 번역본
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices;

	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&vertexBuffer
	);
	assert(SUCCEEDED(hr));

	// Create Vertex Shader
	hr = D3DX11CompileFromFileW 
	(
		L"Effect.hlsl",// Src -> 원본데이터
		nullptr,
		nullptr,
		"VS", // FunctionName -> effect의 VS(함수진입점이름)
		"vs_5_0", //pProfile -> 버전(현재 쓰는 버전은 제일 높은 버전이다)
		0, //uint니까 0으로 한다(쓰지 않는다)
		0,
		nullptr,
		&vsBlob,
		nullptr,
		nullptr
	);
	assert(SUCCEEDED(hr));

	// Shader를 만들어주어야 한다.
	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(), // 컴파일되는 정보를 알려주어야 한다.(시작점)
		vsBlob->GetBufferSize(), // 컴파일되는 정보의 길이를 알려주어야 한다.
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));

	// Create Pixel Shader
	hr = D3DX11CompileFromFileW 
	(
		L"Effect.hlsl",// Src -> 원본데이터
		nullptr,
		nullptr,
		"PS", // FunctionName -> effect의 VS(함수진입점이름)
		"ps_5_0", //pProfile -> 버전(현재 쓰는 버전은 제일 높은 버전이다)
		0, //uint니까 0으로 한다(쓰지 않는다)
		0,
		nullptr,
		&psBlob,
		nullptr,
		nullptr
	);
	assert(SUCCEEDED(hr));

	// Shader를 만들어주어야 한다.
	hr = graphics->GetDevice()->CreatePixelShader
	(
		psBlob->GetBufferPointer(), // 컴파일되는 정보를 알려주어야 한다.(시작점)
		psBlob->GetBufferSize(), // 컴파일되는 정보의 길이를 알려주어야 한다.
		nullptr,
		&pixelShader
	);
	assert(SUCCEEDED(hr));

	// Create Vertex Layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// 배열 크기에 대한 정보
	uint elementCount = ARRAYSIZE(layoutDesc);

	hr = graphics->GetDevice()->CreateInputLayout
	(
		layoutDesc,
		elementCount,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout
	);
	assert(SUCCEEDED(hr));
}

void Game::Update()
{
	graphics->GetDeviceContext()->UpdateSubresource
	(
		vertexBuffer,
		0,
		nullptr,
		vertices,
		sizeof(VertexColor) * 6,
		0
	);
}

void Game::Render()
{
	// stride = 보폭(정점 하나당 크기)
	uint stride = sizeof(VertexColor);
	uint offset = 0;

	graphics->GetDeviceContext()->IASetVertexBuffers
	(
		0,
		1,
		&vertexBuffer,
		&stride,
		&offset
	);
	graphics->GetDeviceContext()->IASetInputLayout(inputLayout);
	// 기본 도형에 대한 정보를 알려준다.
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphics->GetDeviceContext()->VSSetShader
	(
		vertexShader,
		nullptr,
		0
	);
	graphics->GetDeviceContext()->PSSetShader
	(
		pixelShader,
		nullptr,
		0
	);

	graphics->GetDeviceContext()->Draw(6, 0);
}

void Game::Destory()
{
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vsBlob);
	SAFE_DELETE_ARRAY(vertices);
}
