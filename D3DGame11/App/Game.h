#pragma once
#include "App.h"

// ������ �θ� Ŭ�������� ���ǵ� ���������Լ����� ���������ִ� ���
// �ڽ� Ŭ������ �̸� ������ ���콺�� Ŭ���Ѵ�.
// ���� �۾� �� �����͸��� Ŭ���Ѵ�.
// '�ڽ� Ŭ���� �̸�' Ŭ������ ��� ���� ���� �Լ� ������ Ŭ���Ѵ�.

// ���� �����ϱ� ���ؼ��� �ּ� 3���� ���� �ʿ��ϴ�.
// �׷��Ƿ� DX������ �ﰢ���� �������� �Ѵ�.

class Game : public App
{
public:
	Game() {}
	virtual ~Game() {}

	// ���������Լ��� �����Լ��� �������ϴ� ��찡 ������ override�� �ٿ�����

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destory() override;

private:
	class Camera* camera;

	VertexTexture* vertices; // ������ ����� ���ؼ��� ���� �������� �ʿ��ϴ�(�迭�� �־��ش�.)
	uint* indices;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// HLSL���� �ۼ��� vertexShader�� ����ϰڴٰ� GPU�� �˷��ִ� �������� �ʿ��ϴ�.
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	ID3D11InputLayout* inputLayout;

	D3DXMATRIX world;

	// ConstantBuffer
	struct Data
	{
		D3DXMATRIX World;
		D3DXMATRIX View;
		D3DXMATRIX Projection;
	}data;
	ID3D11Buffer* cbuffer;

	// Rasterizer State
	ID3D11RasterizerState* rsState;
	ID3D11RasterizerState* rsState2;

	// Texture
	// View�� Texture�̴�.
	// Texture�� ������ ID3D11Texture2D������ �̰��� Shader�� �־��־�� �ϹǷ� �Ʒ����� ����.
	ID3D11ShaderResourceView* srv;
};
