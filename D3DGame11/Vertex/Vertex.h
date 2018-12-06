#pragma once

// customize vertex

struct Vertex
{
	D3DXVECTOR3 position;
};

struct VertexColor
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};

// UV좌표계 : 특정 텍스쳐를 (0,0), (1,1)로 정규화시켜 만든 좌표계
struct VertexTexture
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;
};