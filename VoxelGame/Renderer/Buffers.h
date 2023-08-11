#pragma once
#include <glad/glad.h>
class VertexBuffer 
{
public:
	VertexBuffer(unsigned int size);
	VertexBuffer(float* vertices, unsigned int size);
	 ~VertexBuffer();
	 void UpdateVerticies(float* vertices, unsigned int size)
	 void Bind() const ;
	 void Unbind() const ;

	 void SetData(const void* data, unsigned int size) ;

	// const BufferLayout& GetLayout() const override { return m_Layout; }
	// void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
private:
	unsigned int m_ID;
	//BufferLayout m_Layout;
};

class IndexBuffer 
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	 ~IndexBuffer();

	 void Bind() const;
	 void Unbind() const;

	 unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_ID;
	unsigned int m_Count;
};