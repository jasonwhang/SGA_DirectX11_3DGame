#pragma once
#include "App.h"


class Game : public App
{
public:
	Game() {}
	virtual ~Game() {}

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destory() override;

private:
	VertexColor * vertices;

	ID3D11Buffer* vertexBuffer;

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	ID3D11InputLayout* inputLayout;

};
