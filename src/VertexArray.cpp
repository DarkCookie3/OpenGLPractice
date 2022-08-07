#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

std::unordered_map<unsigned int, int> VertexArray::numOfInstances;

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::VertexArray(const VertexArray& arg) : m_RendererID(arg.m_RendererID)
{
	numOfInstances[m_RendererID] += 1;
}

VertexArray::VertexArray(VertexArray&& arg) noexcept : m_RendererID(arg.m_RendererID)
{
	arg.m_RendererID = 0;
}

VertexArray& VertexArray::operator=(const VertexArray& arg)
{
	numOfInstances[m_RendererID] -= 1;
	m_RendererID = arg.m_RendererID;
	numOfInstances[m_RendererID] += 1;
	return *this;
}

VertexArray& VertexArray::operator=(VertexArray&& arg) noexcept
{
	numOfInstances[m_RendererID] -= 1;
	m_RendererID = arg.m_RendererID;
	arg.m_RendererID = 0;
	return *this;
}

VertexArray::~VertexArray()
{	
	if (m_RendererID != 0)
	{
		if (numOfInstances[m_RendererID] == 1 && m_RendererID != 0)
		{
			GLCall(glDeleteVertexArrays(1, &m_RendererID));
		}
		numOfInstances[m_RendererID] -= 1;
	}
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
