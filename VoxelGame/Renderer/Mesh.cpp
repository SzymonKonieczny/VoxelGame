#include "Mesh.h"

Mesh::Mesh(MeshType type)
{
	Type = type;
	VertexArray.SetVertexBuffer(new VertexBuffer());
	if (type == MeshType::Indexed)
	{
		VertexArray.SetIndexBuffer(new IndexBuffer());
	}
}

unsigned int Mesh::getCount()
{
	switch (Type)
	{
	case MeshType::Indexed:
		Indicies.size();

		break;
	case MeshType::Unindexed:
		return Verticies.size() / VertexArray.GetLayout().GetElements().size();

		break;
	}
}

void Mesh::Bind()
{
	VertexArray.Bind();
	Shader->Bind();
	if (hasTexture) Texture->Bind();
}

void Mesh::UpdateGLObjs()
{
	VertexArray.UpdateVertexData(Verticies.data(), Verticies.size() * sizeof(float));
}
