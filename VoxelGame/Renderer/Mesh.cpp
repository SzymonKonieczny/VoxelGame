#include "Mesh.h"
#include <iostream>
Mesh::Mesh(MeshType type)
{
	m_VertexArray.reset(new VertexArray());
	m_Type = type;
	m_VertexArray->SetVertexBuffer(new VertexBuffer());
	if (type == MeshType::Indexed)
	{
		m_VertexArray->Bind();
		m_VertexArray->SetIndexBuffer(new IndexBuffer());
	}

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
		return VerticiesSize / test;
		break;
	}
}

void Mesh::Bind()
{
	m_Shader->Bind();
	m_VertexArray->Bind();
	if (hasTexture)
	{
		for (auto& pair : m_Textures)
		{
			glActiveTexture(GL_TEXTURE0 + pair.first);
			pair.second->Bind();
		}
	}



}

void Mesh::SetTexture(unsigned int slot, Texture* texture)
{
	if (m_Textures.contains(slot)) m_Textures[slot].reset(texture);
	else m_Textures.insert({ slot, std::shared_ptr<Texture>(texture) });
}

void Mesh::UpdateObjectsOnGPU()
{
	m_VertexArray->UpdateVertexData(Verticies.data(), Verticies.size() * sizeof(float));
	VerticiesSize = Verticies.size();
	if (m_Type == MeshType::Indexed)
	{
		m_VertexArray->UpdateIndexData(Indicies.data(), Indicies.size());
	}
	//glFlush();
	//Verticies.clear(); causes wierd glitches, kinda like byte/bitwise offsets in data sent to the GPU when swapIntervals is ON
}

void Mesh::PreDraw()
{
	UploadAllUniforms();
}

void Mesh::AddUniform(std::string name, UniformType type)
{
	UniformData.insert(std::make_pair(name, Uniform(type, name)));

}

void Mesh::updateUniform(std::string name, UniformDataUnion data)
{
	UniformData[name].data = data;

}

void Mesh::UploadAllUniforms()
{
	for (auto& uniform : UniformData)
	{

		uploadSingleUniform(uniform.first);

	}
}

void Mesh::uploadSingleUniform(std::string name)
{
	auto& uniform = UniformData[name];
	auto& data = uniform.data;
	switch (uniform.type)
	{
	case UniformType::Int:
		m_Shader->UploadUniformInt(uniform.name, data.Int1);

		break;
	case UniformType::Float:
		m_Shader->UploadUniformFloat(uniform.name, data.Float1);
		break;
	case UniformType::Float2:
		m_Shader->UploadUniformFloat2(uniform.name, data.Float2);

		break;
	case UniformType::Float3:
		m_Shader->UploadUniformFloat3(uniform.name, data.Float3);

		break;
	case UniformType::Float4:
		m_Shader->UploadUniformFloat4(uniform.name, data.Float4);

		break;
	case UniformType::Mat4:
		m_Shader->UploadUniformMat4(uniform.name, data.Mat4);

		break;
	default:
		std::cout << "Using a Uniform type for which uploading wasnt yet implemented. Uniform name :" << uniform.name << "\n";

		break;
	}
}

bool Mesh::hasUniform(std::string name)
{
	return UniformData.contains(name);
}
