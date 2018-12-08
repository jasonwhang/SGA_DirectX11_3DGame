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

	// 특정 vector를 지우는 함수
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
		// offset은 시작지점을 의미한다.
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
	// 외부에서 만들어진 여러개의 vertex를 기존에 만들어진 vertex공간에 한꺼번에 추가하고 싶을 경우
	void AddVertices(const vector<T>& vertices);
	// 외부에서 만들어진 여러개의 vertex를 기존에 추가된 vertex를 지우고 새로 추가하고 싶을 경우
	void SetVertices(const vector<T>& vertices);

	void AddIndex(const uint& index);
	void AddIndices(const vector<uint>& indices);
	void SetIndicies(const vector<uint>& indices);

private:
	// 동적할당이 되는 것이 아니다. 지역변수이다.
	vector<T> vertices;
	vector<uint> indices;
};

#include "Geometry.inl"
