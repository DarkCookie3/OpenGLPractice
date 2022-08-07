#include "IndexBuffer.h"
#include "Renderer.h"

std::unordered_map<unsigned int, int> IndexBuffer::numOfInstances;

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer()
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

IndexBuffer::IndexBuffer(const IndexBuffer& arg) : m_RendererID(arg.m_RendererID), m_Count(arg.m_Count)
{
    numOfInstances[m_RendererID] += 1;
}

IndexBuffer::IndexBuffer(IndexBuffer&& arg) noexcept : m_RendererID(arg.m_RendererID), m_Count(arg.m_Count)
{
    arg.m_RendererID = 0;
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& arg)
{
    numOfInstances[m_RendererID] -= 1;
    m_RendererID = arg.m_RendererID;
    m_Count = arg.m_Count;
    numOfInstances[m_RendererID] += 1;
    return *this;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& arg) noexcept
{
    numOfInstances[m_RendererID] -= 1;
    m_RendererID = arg.m_RendererID;
    m_Count = arg.m_Count;
    arg.m_RendererID = 0;
    return *this;
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


