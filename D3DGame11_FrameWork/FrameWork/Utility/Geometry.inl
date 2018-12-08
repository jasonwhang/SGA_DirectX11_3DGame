#include "Geometry.h"

template<class T>
inline Geometry<T>::Geometry()
{
}

template<class T>
inline Geometry<T>::~Geometry()
{
}

template<class T>
inline void Geometry<T>::Clear()
{
	// clear는 안에 있는 내용을 지우는 것이지 추가된 데이터만큼의 크기의 공간은 남아있다.
	vertices.clear();
	// 비어진 늘려난 공간을 줄여주는 역할이다.
	vertices.shrink_to_fit();

	indices.clear();
	indices.shrink_to_fit();
}

template<class T>
inline void Geometry<T>::GetGeometry(vector<T>& vertices, vector<uint>& indices)
{
	vertices = this->vertices;
	indices = this->indices;
}

template<class T>
inline void Geometry<T>::GetGeometry(const uint & vertexOffset,
	const uint & vertexCount, const uint & indexOffset, 
	const uint & indexCount, vector<T>& vertices, vector<uint>& indices)
{
	GetVertices(vertexOffset, vertexCount, vertices);
	GetIndices(indexOffset, indexCount, indices);
}

template<class T>
inline void Geometry<T>::GetVertices(const uint & offset, const uint & count, vector<T>& vertices)
{
	auto first = this->vertices.begin() + offset;
	auto last = this->vertices.begin() + offset + count;

	vertices.assign(first, last);
}

template<class T>
inline void Geometry<T>::GetIndices(const uint & offset, const uint & count, vector<uint>& indices)
{
	auto first = this->indicies.begin() + offset;
	auto last = this->indicies.begin() + offset + count;

	indices.assign(first, last);
}

template<class T>
inline void Geometry<T>::AddVertex(const T & vertex)
{
	vertices.emplace_back(vertex);
}

template<class T>
inline void Geometry<T>::AddVertices(const vector<T>& vertices)
{
	this->vertices.insert
	(
		// vertices가 들어가는 vertex공간의 끝에다가 들어가는 vertices의 시작부터 끝까지 전부 넣으면 된다.
		this->vertices.end(),
		vertices.begin(),
		vertices.end()
	);
}

template<class T>
inline void Geometry<T>::SetVertices(const vector<T>& vertices)
{
	Clear();
	this->vertices.assign(vertices.begin(), vertices.end());
}

template<class T>
inline void Geometry<T>::AddIndex(const uint & index)
{
	indices.emplace_back(index);
}

template<class T>
inline void Geometry<T>::AddIndices(const vector<uint>& indices)
{
	this->indices.insert
	(
		this->indices.end(),
		indices.begin(),
		indices.end()
	);
}

template<class T>
inline void Geometry<T>::SetIndicies(const vector<uint>& indices)
{
	Clear();
	this->indices.assign(indices.begin(), indices.end());
}