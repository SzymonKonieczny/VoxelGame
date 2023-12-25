#pragma once
#include <glad/glad.h>
#include "Buffers.h"
#include <memory>
class VertexArray {
public:
	VertexArray();
	VertexArray(unsigned int size);
	VertexArray(float* vertices, unsigned int size);
	virtual ~VertexArray();
	void SetIndexBuffer(std::shared_ptr < IndexBuffer>& indexBuffer);
	void SetIndexBuffer(IndexBuffer* indexBuffer);


	void SetVertexBuffer( std::shared_ptr<VertexBuffer>& vertexBuffer);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);

	void UpdateVertexData(float* vertices, unsigned int size);
	void UpdateIndexData(unsigned int* indicies, unsigned int count);

	 void Bind() const ;
	 void Unbind() const ;

	 void SetData(const void* data, unsigned int size) ;

	const BufferLayout& GetLayout() const  { return m_Vertexbuffer->GetLayout(); }
	void SetLayout(const BufferLayout& layout)  { m_Vertexbuffer->SetLayout(layout); UpdateVertexBufferLayoutAttributes();}

	void UpdateVertexBufferLayoutAttributes();
private:
	unsigned int m_ID;

	std::shared_ptr<IndexBuffer> m_Inderbuffer;
	std::shared_ptr<VertexBuffer> m_Vertexbuffer;
};