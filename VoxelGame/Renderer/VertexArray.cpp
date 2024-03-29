#include "VertexArray.h"
#include <iostream>
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return GL_FLOAT;
	case ShaderDataType::Float2:   return GL_FLOAT;
	case ShaderDataType::Float3:   return GL_FLOAT;
	case ShaderDataType::Float4:   return GL_FLOAT;
	case ShaderDataType::Mat3:     return GL_FLOAT;
	case ShaderDataType::Mat4:     return GL_FLOAT;
	case ShaderDataType::Int:      return GL_INT;
	case ShaderDataType::Int2:     return GL_INT;
	case ShaderDataType::Int3:     return GL_INT;
	case ShaderDataType::Int4:     return GL_INT;
	case ShaderDataType::Bool:     return GL_BOOL;
	}

	return 0;
}

VertexArray::VertexArray()
{

	glCreateVertexArrays(1, &m_ID);
}

VertexArray::VertexArray(unsigned int size)
{
	glCreateVertexArrays(1, &m_ID);

}

VertexArray::VertexArray(float* vertices, unsigned int size)
{
	glCreateVertexArrays(1, &m_ID);

}

VertexArray::~VertexArray()
{
	//std::cout << "Deleting VertexArray id " << m_ID << "\n";

	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{

	glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{

	glBindVertexArray(0);
}

void VertexArray::SetData(const void* data, unsigned int size)
{
	std::cout << "using an unimplemented function VertexArray::SetData.";
	int a = *(int*)0; //
}

void VertexArray::UpdateVertexBufferLayoutAttributes()
{
	const auto& layout = m_Vertexbuffer->GetLayout();
	for (int i = 0; i < layout.GetElements().size(); i++)
	{
		auto& element = layout.GetElements()[i];
		switch (element.Type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			break;
		}
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
		case ShaderDataType::Bool:
		{
			glEnableVertexAttribArray(i);
			glVertexAttribIPointer(i,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				layout.GetStride(),
				(const void*)element.Offset);
			break;
		}
		//Mat3 and Mat4 here, if i ever need it ?
		default:
			std::cout << "ShaderDataType unimplemented";
			int a = *(int*)0; //
			break;
		}
	}
}

void VertexArray::SetVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
{


	Bind();
	vertexBuffer->Bind();
	m_Vertexbuffer = vertexBuffer;
	UpdateVertexBufferLayoutAttributes();
}

void VertexArray::SetVertexBuffer(VertexBuffer* vertexBuffer)
{


	m_Vertexbuffer.reset(vertexBuffer);
	Bind();
	m_Vertexbuffer->Bind();
	UpdateVertexBufferLayoutAttributes();
}
void VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
{


	m_Inderbuffer.reset(indexBuffer);
	Bind();
	m_Inderbuffer->Bind();
	//UpdateVertexBufferLayoutAttributes();
}
void VertexArray::UpdateVertexData(float* vertices, unsigned int size)
{
	Bind();
	m_Vertexbuffer->UpdateVerticies(vertices, size);
}

void VertexArray::UpdateIndexData(unsigned int* indicies, unsigned int count)
{
	Bind();
	m_Inderbuffer->UpdateIndicies(indicies, count);
}



void VertexArray::SetIndexBuffer(std::shared_ptr < IndexBuffer>& indexBuffer)
{

	glBindVertexArray(m_ID);
	indexBuffer->Bind();

	m_Inderbuffer = indexBuffer;
}
