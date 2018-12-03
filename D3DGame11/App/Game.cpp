#include "stdafx.h"
#include "Game.h"

void Game::Initialize()
{
	// Create Vertex Data(����������)
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

	// Create VertexBuffer(������)
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexColor) * 6;

	// ���������� ������������ ������ ���� ������
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
		L"Effect.hlsl",// Src -> ����������
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

	// Create Pixel Shader
	hr = D3DX11CompileFromFileW 
	(
		L"Effect.hlsl",// Src -> ����������
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

	// Create Vertex Layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
	// stride = ����(���� �ϳ��� ũ��)
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
	// �⺻ ������ ���� ������ �˷��ش�.
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
