#pragma once
#include "stdafx.h"

template<class T>
class Geometry
{
public:
	Geometry();
	virtual ~Geometry();

	const uint GetVerticesCount() const { return vertices.size(); }
	const uint GetIndicesCount() const { return indices.size(); }
	const uint GetTriangleCount() const { return indices.size() / 3; }

	// Ư�� vector�� ����� �Լ�
	void Clear();

	void GetGeometry(vector<T>& vertices, vector<uint>& indices);
	void GetGeometry
	(
		const uint& vertexOffset,
		const uint& vertexCount,
		const uint& indexOffset,
		const uint& indexCount,
		vector<T>& vertices,
		vector<uint>& indices
	);

	const vector<T>& GetVertices()  const { return vertices; }
	void GetVertices
	(
		// offset�� ���������� �ǹ��Ѵ�.
		const uint& offset,
		const uint& count,
		vector<T>& vertices
	);

	const vector<uint>& GetIndices() const { return indices; }
	void GetIndices
	(
		const uint& offset,
		const uint& count,
		vector<uint>& indices
	);

	void AddVertex(const T& vertex);
	// �ܺο��� ������� �������� vertex�� ������ ������� vertex������ �Ѳ����� �߰��ϰ� ���� ���
	void AddVertices(const vector<T>& vertices);
	// �ܺο��� ������� �������� vertex�� ������ �߰��� vertex�� ����� ���� �߰��ϰ� ���� ���
	void SetVertices(const vector<T>& vertices);

	void AddIndex(const uint& index);
	void AddIndices(const vector<uint>& indices);
	void SetIndicies(const vector<uint>& indices);

private:
	// �����Ҵ��� �Ǵ� ���� �ƴϴ�. ���������̴�.
	vector<T> vertices;
	vector<uint> indices;
};

#include "Geometry.inl"
