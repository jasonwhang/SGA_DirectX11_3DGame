#include "stdafx.h"
#include "Game.h"
#include "../Camera/Camera.h"

// ../ �� ������ ���� ����
// ./ �� ���� ��

// ������ ���� ���� �ð���� ������� ����־�� �Ѵ�.(�޼���ǥ��)

void Game::Initialize()
{
#pragma region Camera
	camera = new Camera();
	camera->SetOrthographicLH(1280, 720, 0, 1);
	//camera->SetOrthographicOffCenterLH(0, 1280, 720, 0, 0, 1);
	//camera->SetOrthographicOffCenterLH(0, 1280, 0, 720, 0, 1);
#pragma endregion

#pragma region Create VertexBuffer(����������)

	vertices = new VertexTexture[4];

	vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // 0
	vertices[0].uv = D3DXVECTOR2(0, 1);

	vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); //1
	vertices[1].uv = D3DXVECTOR2(0, 0);

	vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); //2
	vertices[2].uv = D3DXVECTOR2(1, 1);

	vertices[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); //3
	vertices[3].uv = D3DXVECTOR2(1, 0);

	// Create VertexBuffer(������)
	// ���⿡���� ������ ������ش�.
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	// �� ���۸� ��� ����� ���ΰ��� ���ϴ� �� = �⺻���� ����Ѵ�
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // �������� ����� ����� ����Ѵ�(�⺻��)
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// �� ������ ũ��(vertex data�� ũ��(6��))
	bufferDesc.ByteWidth = sizeof(VertexTexture) * 4;

	// ���������� ������������ ������ ���� ������
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	// ������������ �������� pSysMem�� �˾Ƽ� �������ش�.
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
	// �迭�� �ٷ� �ʱ�ȭ�ϴ� ���
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

	hr = D3DX11CompileFromFileW  // ->HLSL�� ������Ʈ���� ���������� �ʱ� ������ ���� �������ϴ� �Լ��� ������ش�.
	(
		L"Texture.hlsl",// Src -> ����������
		nullptr,
		nullptr,
		"VS", // FunctionName -> effect�� VS(�Լ��������̸�)
		"vs_5_0", //pProfile -> ����(���� ���� ������ ���� ���� �����̴�)
		0, //uint�ϱ� 0���� �Ѵ�(���� �ʴ´�)
		0,
		nullptr,
		&vsBlob,
		nullptr,
		nullptr
	);
	assert(SUCCEEDED(hr));

	// Shader�� ������־�� �Ѵ�.
	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(), // �����ϵǴ� ������ �˷��־�� �Ѵ�.(������)
		vsBlob->GetBufferSize(), // �����ϵǴ� ������ ���̸� �˷��־�� �Ѵ�.
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));

#pragma endregion

#pragma region  Create Pixel Shader

	hr = D3DX11CompileFromFileW  // ->HLSL�� ������Ʈ���� ���������� �ʱ� ������ ���� �������ϴ� �Լ��� ������ش�.
	(
		L"Texture.hlsl",// Src -> ����������
		nullptr,
		nullptr,
		"PS", // FunctionName -> effect�� VS(�Լ��������̸�)
		"ps_5_0", //pProfile -> ����(���� ���� ������ ���� ���� �����̴�)
		0, //uint�ϱ� 0���� �Ѵ�(���� �ʴ´�)
		0,
		nullptr,
		&psBlob,
		nullptr,
		nullptr
	);
	assert(SUCCEEDED(hr));

	// Shader�� ������־�� �Ѵ�.
	hr = graphics->GetDevice()->CreatePixelShader
	(
		psBlob->GetBufferPointer(), // �����ϵǴ� ������ �˷��־�� �Ѵ�.(������)
		psBlob->GetBufferSize(), // �����ϵǴ� ������ ���̸� �˷��־�� �Ѵ�.
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

	// �迭 ũ�⿡ ���� ����
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
	// ī�޶��� ���۴� �ǽð����� ������ �ٲ��� �Ѵ�.
	cbufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbufferDesc.ByteWidth = sizeof(Data);
	// ī�޶� CPU�� �ְ� HLSL�� GPU�� �ִ�.
	// HLSL���� ������� ���� CPU�� �ޱ⸸ �ϸ� �ȴ�.
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

	// ����� ���ҿ� �����ϴ� ��� (1,1)�� �����ϰڴ�.
	world._11 = 100;
	world._22 = 100;

	D3DXMatrixTranspose(&data.World, &world);
	D3DXMatrixTranspose(&data.View, &camera->GetViewMatrix());
	D3DXMatrixTranspose(&data.Projection, &camera->GetProjecttionMatrix());

	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	// Update ���� cbuffer�� ���� �����ϰ� �ƹ��� �о������ ���ϵ��� ��踦 ġ�� ���̴�.
	graphics->GetDeviceContext()->Map(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&subResource
	);
	// subResource�� �ٲ� ������ ���� �������� ����´�.
	memcpy(subResource.pData, &data, sizeof(Data));

	graphics->GetDeviceContext()->Unmap(cbuffer, 0);
}

void Game::Render()
{
	// stride = ����(���� �ϳ��� ũ��)
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

	// �⺻ ������ ���� ������ �˷��ش�.
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
		1, // texture�� 1�� �ִ´�
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
