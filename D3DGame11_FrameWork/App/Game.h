#pragma once
#include "App.h"

// 빠르게 부모 클래스에서 정의된 순수가상함수들을 재정의해주는 방법
// 자식 클래스의 이름 오른쪽 마우스를 클릭한다.
// 빠른 작업 및 리팩터링을 클릭한다.
// '자식 클래스 이름' 클래스의 모든 순수 가상 함수 구현을 클릭한다.

// 면을 생성하기 위해서는 최소 3개의 점이 필요하다.
// 그러므로 DX에서는 삼각형을 기준으로 한다.

class Game : public App
{
public:
	Game() {}
	virtual ~Game() {}

	// 순수가상함수나 가상함수를 재정의하는 경우가 있으면 override를 붙여주자

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
