#include "Buffers.h"
VertexBuffer::VertexBuffer(unsigned int size)
{

}

VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::UpdateVerticies(float* vertices, unsigned int size)
{

}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void VertexBuffer::SetData(const void* data, unsigned int size)
{

}

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
}

void IndexBuffer::Unbind() const
{
}
