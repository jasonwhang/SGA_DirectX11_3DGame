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

// UV��ǥ�� : Ư�� �ؽ��ĸ� (0,0), (1,1)�� ����ȭ���� ���� ��ǥ��
struct VertexTexture
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;
};