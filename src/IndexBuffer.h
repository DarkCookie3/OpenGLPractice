#pragma once
#include <unordered_map>

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
	static std::unordered_map<unsigned int, int> numOfInstances;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(const IndexBuffer& arg);
	IndexBuffer(IndexBuffer&& arg) noexcept;

	IndexBuffer& operator=(const IndexBuffer& arg);
	IndexBuffer& operator=(IndexBuffer&& arg) noexcept;

	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const
	{
		return m_Count;
	}
};