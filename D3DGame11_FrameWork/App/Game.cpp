#include "stdafx.h"
#include "Game.h"


void Game::Initialize()
{
	graphics = context->GetSubsystem<Graphics>();


	geometry.AddVertex(VertexTexture(D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXVECTOR2(0, 1)));
	geometry.AddVertex(VertexTexture(D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXVECTOR2(0, 0)));
	geometry.AddVertex(VertexTexture(D3DXVECTOR3(0.5f, -0.5f, 0.0f), D3DXVECTOR2(2, 1)));
	geometry.AddVertex(VertexTexture(D3DXVECTOR3(0.5f, 0.5f, 0.0f), D3DXVECTOR2(2, 0)));

	geometry.AddIndex(0); geometry.AddIndex(1); geometry.AddIndex(2);
	geometry.AddIndex(2); geometry.AddIndex(1); geometry.AddIndex(3);

#pragma region Create Vertex Buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexTexture) * geometry.GetVerticesCount();

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = geometry.GetVertices().data();

	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&vertexBuffer
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region Create Index Buffer
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(uint) * geometry.GetIndicesCount();

	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = geometry.GetIndices().data();

	hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&indexBuffer
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region Compile Texture Vertex Shader hlsl
	hr = D3DX11CompileFromFile
	(
		L"TextureCoord.hlsl",
		nullptr,
		nullptr,
		"VS",
		"vs_5_0",
		0,
		0,
		nullptr,
		&vsBlob,
		nullptr,
		nullptr
	);
#pragma endregion

#pragma region Create Vertex Shader
	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region Compile Texture Pixel Shader hlsl
	hr = D3DX11CompileFromFile
	(
		L"TextureCoord.hlsl",
		nullptr,
		nullptr,
		"PS",
		"ps_5_0",
		0,
		0,
		nullptr,
		&psBlob,
		nullptr,
		nullptr
	);
#pragma endregion

#pragma region Create Pixel Shader
	hr = graphics->GetDevice()->CreatePixelShader
	(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		nullptr,
		&pixelShader
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region Input Layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		// R = x, G  = y, B = z, A = w랑 매칭된다.
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	uint elementCount = ARRAYSIZE(layoutDesc);
	hr = graphics->GetDevice()->CreateInputLayout
	(
		layoutDesc,
		elementCount,
		// 레이아웃을 하는 정보가 vertex에 있기 때문에 vsBlob에서 가져온다.
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region Create Shader Resource View
	hr = D3DX11CreateShaderResourceViewFromFile
	(
		graphics->GetDevice(),
		L"Tree.png",
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
#pragma endregion

#pragma region Create Shader Resource View2
	hr = D3DX11CreateShaderResourceViewFromFile
	(
		graphics->GetDevice(),
		L"BackGround.png",
		nullptr,
		nullptr,
		&srv2,
		nullptr
	);
#pragma endregion

#pragma region Create Constant Buffer
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = sizeof(Data);

	hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		nullptr,
		&cbuffer
	);
	assert(SUCCEEDED(hr));
#pragma endregion

#pragma region World
	D3DXMatrixIdentity(&world);
#pragma endregion

#pragma region View
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 1), &D3DXVECTOR3(0, 1, 0));
#pragma endregion

#pragma region Projection
	D3DXMatrixIdentity(&projection);
	D3DXMatrixOrthoLH(&projection, 1280, 720, 0, 1);
#pragma endregion
}

void Game::Update()
{
	world._11 = 500; // x의 크기
	world._22 = 500; // y의 크기

	D3DXMatrixTranspose(&data.World, &world);
	D3DXMatrixTranspose(&data.View, &view);
	D3DXMatrixTranspose(&data.Projection, &projection);

	D3D11_MAPPED_SUBRESOURCE subresource;
	graphics->GetDeviceContext()->Map
	(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&subresource
	);

	memcpy(subresource.pData, &data, sizeof(Data));

	graphics->GetDeviceContext()->Unmap(cbuffer, 0);
}

void Game::Render()
{
	uint stride = sizeof(VertexTexture);
	uint offset = 0;

#pragma region Pipeline_IA
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	graphics->GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	graphics->GetDeviceContext()->IASetInputLayout(inputLayout);
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#pragma endregion

#pragma region Pipeline_VS
	graphics->GetDeviceContext()->VSSetShader(vertexShader, nullptr, 0); // 0 = 안쓴다는 의미
	graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &cbuffer); // register : b0
#pragma endregion

#pragma region Pipeline_PS
	graphics->GetDeviceContext()->PSSetShader(pixelShader, nullptr, 0);
	graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &srv); // register : t0
	graphics->GetDeviceContext()->PSSetShaderResources(1, 1, &srv2); // register : t0

#pragma endregion

#pragma region Pipeline_OM																
	// Graphics에서 OMSetRenderTargetView를 해준다.
	graphics->GetDeviceContext()->DrawIndexed(
		geometry.GetIndicesCount(),
		0, //Index시작지점 : 0번
		0 // Vertex시작지점 : 0번
	);
#pragma endregion
}

void Game::Destory()
{
	SAFE_RELEASE(cbuffer);
	SAFE_RELEASE(srv);
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);
}
