#include "Buffers.h"
#include <iostream>
VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_ID);
	Bind();
}


VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	std::cout << "Deleting vert buffer id "<< m_ID<<"\n";

	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::UpdateVerticies(float* vertices, unsigned int size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
	std::cout << "using an unimplemented function VertexBuffer::SetData. Did you mean VertexBuffer::UpdateVerticies ?";
	int a = *(int*)0; //
}

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
{

					// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
					// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
					//glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	m_Count = count;
}

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &m_ID);
	Bind();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);

}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void IndexBuffer::UpdateIndicies(unsigned int* indices, unsigned int count)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	m_Count = count;
}
