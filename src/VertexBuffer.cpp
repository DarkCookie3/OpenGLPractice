#include "VertexBuffer.h"
#include "Renderer.h"

std::unordered_map<unsigned int, int> VertexBuffer::numOfInstances;

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const VertexBuffer& arg) : m_RendererID(arg.m_RendererID)
{
    numOfInstances[m_RendererID] += 1;
}

VertexBuffer::VertexBuffer(VertexBuffer&& arg) noexcept : m_RendererID(arg.m_RendererID)
{
    arg.m_RendererID = 0;
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& arg)
{
    m_RendererID = arg.m_RendererID;
    numOfInstances[m_RendererID] += 1;
    return *this;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& arg) noexcept
{
    m_RendererID = arg.m_RendererID;
    arg.m_RendererID = 0;
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    if (m_RendererID != 0)
    {
        if (numOfInstances[m_RendererID] == 1 && m_RendererID != 0)
        {
            GLCall(glDeleteBuffers(1, &m_RendererID));
        }
        numOfInstances[m_RendererID] -= 1;
    }
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
