#pragma once
class VertexArray {
public:
	VertexArray(unsigned int size);
	VertexArray(float* vertices, unsigned int size);
	virtual ~VertexArray();

	 void Bind() const ;
	 void Unbind() const ;

	 void SetData(const void* data, unsigned int size) ;

	// const BufferLayout& GetLayout() const  { return m_Layout; }
	// void SetLayout(const BufferLayout& layout)  { m_Layout = layout; }
private:
	unsigned int m_ID;
	//BufferLayout m_Layout;
};