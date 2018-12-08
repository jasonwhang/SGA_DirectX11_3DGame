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
	class Graphics* graphics;

	class Geometry<VertexTexture> geometry;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11InputLayout* inputLayout;

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv2;

	struct Data
	{
		D3DXMATRIX World;
		D3DXMATRIX View;
		D3DXMATRIX Projection;
	}data;

	ID3D11Buffer* cbuffer;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

};
