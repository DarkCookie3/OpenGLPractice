#pragma once
#include <unordered_map>

class VertexBuffer
{
private:
	unsigned int m_RendererID;
	static std::unordered_map<unsigned int, int> numOfInstances;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const VertexBuffer& arg);
	VertexBuffer(VertexBuffer&& arg) noexcept;

	VertexBuffer& operator=(const VertexBuffer& arg);
	VertexBuffer& operator=(VertexBuffer&& arg) noexcept;

	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};