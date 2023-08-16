#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>
enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static unsigned int ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return 4;
	case ShaderDataType::Float2:   return 4 * 2;
	case ShaderDataType::Float3:   return 4 * 3;
	case ShaderDataType::Float4:   return 4 * 4;
	case ShaderDataType::Mat3:     return 4 * 3 * 3;
	case ShaderDataType::Mat4:     return 4 * 4 * 4;
	case ShaderDataType::Int:      return 4;
	case ShaderDataType::Int2:     return 4 * 2;
	case ShaderDataType::Int3:     return 4 * 3;
	case ShaderDataType::Int4:     return 4 * 4;
	case ShaderDataType::Bool:     return 1;
	}

	return 0;
}

struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	uint32_t Size;
	size_t Offset;
	bool Normalized;

	BufferElement() = default;

	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{
	}

	uint32_t GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3; //chyba,3 * float3 for now zostaje tak 
		case ShaderDataType::Mat4:    return 4; //chyba,4 * float4 for now zostaje tak 
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}

		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout() {}

	BufferLayout(std::initializer_list<BufferElement> elements) //has to be an initializer list since we cant do double casts from initializerlist to vector to BufferLayout(vector)
		: m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	uint32_t GetStride() const { return m_Stride; }
	const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	//std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	//std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	//std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	//std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
private:
	void CalculateOffsetsAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			m_Stride += element.Size;
			offset += element.Size;
		}
	}
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};
class VertexBuffer 
{
public:
	VertexBuffer();
	VertexBuffer(float* vertices, unsigned int size);
	 ~VertexBuffer();
	 void UpdateVerticies(float* vertices, unsigned int size);
	 void Bind() const ;
	 void Unbind() const ;

	 void SetData(const void* data, unsigned int size) ;

	 const BufferLayout& GetLayout() const  { return m_Layout; }
	 void SetLayout(const BufferLayout& layout)  { m_Layout = layout; }
private:
	unsigned int m_ID;
	BufferLayout m_Layout;
};

class IndexBuffer 
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	IndexBuffer();

	 ~IndexBuffer();

	 void Bind() const;
	 void Unbind() const;
	 void UpdateIndicies(unsigned int* indices, unsigned int count);
	 unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_ID;
	unsigned int m_Count;
};