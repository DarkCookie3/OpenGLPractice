#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
	static std::unordered_map<unsigned int, int> numOfInstances;
public:
	VertexArray();
	VertexArray(const VertexArray& arg);
	VertexArray(VertexArray&& arg) noexcept;

	VertexArray& operator=(const VertexArray& arg);
	VertexArray& operator=(VertexArray&& arg) noexcept;

	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};