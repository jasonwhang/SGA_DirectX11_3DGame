#pragma once

// customize vertex

struct Vertex
{
	Vertex()
		: position(0, 0, 0) {}

	Vertex(const D3DXVECTOR3& position)
		: position(position) {}

	D3DXVECTOR3 position;
};

struct VertexColor
{
	VertexColor()
		: position(0, 0, 0)
		, color(0, 0, 0, 1)
	{}

	VertexColor(const D3DXVECTOR3& position, const D3DXCOLOR& color)
		: position(position)
		, color(color)
	{}

	D3DXVECTOR3 position;
	D3DXCOLOR color;
};

// UV��ǥ�� : Ư�� �ؽ��ĸ� (0,0), (1,1)�� ����ȭ���� ���� ��ǥ��
struct VertexTexture
{
	VertexTexture()
		: position(0, 0, 0)
		, uv(0, 0)
	{}

	VertexTexture(const D3DXVECTOR3& position, const D3DXVECTOR2& uv)
		: position(position)
		, uv(uv)
	{}

	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;
};