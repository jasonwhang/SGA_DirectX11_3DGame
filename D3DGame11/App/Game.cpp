#include "stdafx.h"
#include "Game.h"
#include "../Camera/Camera.h"

// ../ 내 폴더의 위에 폴더
// ./ 내 폴더 안

// 정점을 찍을 때는 시계방향 순서대로 찍어주어야 한다.(왼손좌표계)

void Game::Initialize()
{
#pragma region Camera
	camera = new Camera();
	camera->SetOrthographicLH(1280, 720, 0, 1);
	//camera->SetOrthographicOffCenterLH(0, 1280, 720, 0, 0, 1);
	//camera->SetOrthographicOffCenterLH(0, 1280, 0, 720, 0, 1);
#pragma endregion

#pragma region Create VertexBuffer(원본데이터)

	vertices = new VertexTexture[4];

	vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // 0
	vertices[0].uv = D3DXVECTOR2(0, 1);

	vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); //1
	vertices[1].uv = D3DXVECTOR2(0, 0);

	vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); //2
	vertices[2].uv = D3DXVECTOR2(1, 1);

	vertices[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); //3
	vertices[3].uv = D3DXVECTOR2(1, 0);

	// Create VertexBuffer(번역본)
	// 여기에서는 공간만 만들어준다.
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	// 이 버퍼를 어떻게 사용할 것인가를 정하는 것 = 기본값을 사용한다
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // 정적으로 만드는 방식을 사용한다(기본갑)
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// 이 버퍼의 크기(vertex data의 크기(6개))
	bufferDesc.ByteWidth = sizeof(VertexTexture) * 4;

	// 실질적으로 원본데이터의 정보가 들어가는 번역본
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	// 원본데이터의 정보들을 pSysMem가 알아서 복사해준다.
	subData.pSysMem = vertices;

	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&vertexBuffer
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region 	Create Index Buffer
	// 배열을 바로 초기화하는 방법
	indices = new uint[6]{ 0,1,2,2,1,3 };

	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(uint) * 6;

	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = indices;

	hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&indexBuffer
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region  Create Vertex Shader

	hr = D3DX11CompileFromFileW  // ->HLSL은 프로젝트에서 컴파일하지 않기 때문에 따로 컴파일하는 함수를 만들어준다.
	(
		L"Texture.hlsl",// Src -> 원본데이터
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

#pragma endregion

#pragma region  Create Pixel Shader

	hr = D3DX11CompileFromFileW  // ->HLSL은 프로젝트에서 컴파일하지 않기 때문에 따로 컴파일하는 함수를 만들어준다.
	(
		L"Texture.hlsl",// Src -> 원본데이터
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
#pragma endregion

#pragma region Create Vertex Layout

	//D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	//};

	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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

#pragma endregion

#pragma region  Create ConstantBuffer

	D3D11_BUFFER_DESC cbufferDesc;
	ZeroMemory(&cbufferDesc, sizeof(D3D11_BUFFER_DESC));
	// 카메라의 버퍼는 실시간으로 정보가 바뀌어야 한다.
	cbufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbufferDesc.ByteWidth = sizeof(Data);
	// 카메라가 CPU에 있고 HLSL이 GPU에 있다.
	// HLSL에서 계산해준 값을 CPU는 받기만 하면 된다.
	cbufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = graphics->GetDevice()->CreateBuffer
	(
		&cbufferDesc, nullptr, &cbuffer
	);
	assert(SUCCEEDED(hr));
#pragma endregion

	D3DXMatrixIdentity(&world);

#pragma region  Create Rasterizer State

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.FrontCounterClockwise = false;

	hr = graphics->GetDevice()->CreateRasterizerState
	(
		&rsDesc,
		&rsState
	);
	assert(SUCCEEDED(hr));
#pragma endregion

	//rsDesc.FillMode = D3D11_FILL_SOLID;

	//hr = graphics->GetDevice()->CreateRasterizerState
	//(
	//	&rsDesc,
	//	&rsState2
	//);
	//assert(SUCCEEDED(hr));

#pragma region Create Texture
	hr = D3DX11CreateShaderResourceViewFromFileA
	(
		graphics->GetDevice(),
		"Tree.png",
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	assert(SUCCEEDED(hr));
#pragma endregion
}

void Game::Update()
{

	//graphics->GetDeviceContext()->UpdateSubresource
	//(
	//	vertexBuffer,
	//	0,
	//	nullptr,
	//	vertices,
	//	sizeof(VertexColor) * 6,
	//	0
	//);

	// 행렬의 원소에 접근하는 방법 (1,1)에 접근하겠다.
	world._11 = 100;
	world._22 = 100;

	D3DXMatrixTranspose(&data.World, &world);
	D3DXMatrixTranspose(&data.View, &camera->GetViewMatrix());
	D3DXMatrixTranspose(&data.Projection, &camera->GetProjecttionMatrix());

	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	// Update 중인 cbuffer에 나를 제외하고 아무도 읽어들이지 못하도록 결계를 치는 것이다.
	graphics->GetDeviceContext()->Map(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&subResource
	);
	// subResource가 바뀐 정보에 대한 정보들을 적어온다.
	memcpy(subResource.pData, &data, sizeof(Data));

	graphics->GetDeviceContext()->Unmap(cbuffer, 0);
}

void Game::Render()
{
	// stride = 보폭(정점 하나당 크기)
	uint stride = sizeof(VertexTexture);
	uint offset = 0;

#pragma region Pipeline_IA
	graphics->GetDeviceContext()->IASetVertexBuffers
	(
		0,
		1,
		&vertexBuffer,
		&stride,
		&offset
	);
	graphics->GetDeviceContext()->IASetInputLayout(inputLayout);
	graphics->GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// 기본 도형에 대한 정보를 알려준다.
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#pragma endregion

#pragma region Pipeline_VS

	graphics->GetDeviceContext()->VSSetShader
	(
		vertexShader,
		nullptr,
		0
	);
	graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &cbuffer);

#pragma endregion

#pragma region Pipeline_RS

	graphics->GetDeviceContext()->RSSetState(rsState);

#pragma endregion

#pragma region Pipeline_PS

	graphics->GetDeviceContext()->PSSetShader
	(
		pixelShader,
		nullptr,
		0
	);
	graphics->GetDeviceContext()->PSSetShaderResources
	(
		0, //t0
		1, // texture를 1개 넣는다
		&srv
	);

#pragma endregion

#pragma region Draw

	graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);

#pragma endregion

#pragma region Pipline_ResetRS

	//ID3D11RasterizerState* back = nullptr;
	//graphics->GetDeviceContext()->RSGetState(&back);

	////graphics->GetDeviceContext()->RSSetState(rsState2);
	//graphics->GetDeviceContext()->RSSetState(back);

#pragma endregion
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
