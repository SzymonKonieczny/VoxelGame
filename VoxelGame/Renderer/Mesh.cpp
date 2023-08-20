#include "Mesh.h"
#include <iostream>
Mesh::Mesh(MeshType type)
{
	m_VertexArray.reset(new VertexArray());
	m_Type = type;
	m_VertexArray->SetVertexBuffer(new VertexBuffer());
	if (type == MeshType::Indexed)
	{
		m_VertexArray->SetIndexBuffer(new IndexBuffer());
	}
	std::cout << "Mesh constructed\n";
}

unsigned int Mesh::getCount()
{
	switch (m_Type)
	{
	case MeshType::Indexed:
		Indicies.size();

		break;
	case MeshType::Unindexed:
		int test = m_VertexArray->GetLayout().GetStride()/sizeof(float);
		return Verticies.size() / test;

		break;
	}
}

void Mesh::Bind()
{
	m_VertexArray->Bind();
	m_Shader->Bind();
	if (hasTexture) m_Texture->Bind();
}

void Mesh::UpdateGLObjs()
{
	m_VertexArray->UpdateVertexData(Verticies.data(), Verticies.size() * sizeof(float));
}
