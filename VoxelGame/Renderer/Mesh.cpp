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


	//Very bad for performance, very temporary
	UpdateObjectsOnGPU();
}

void Mesh::UpdateObjectsOnGPU()
{
	m_VertexArray->UpdateVertexData(Verticies.data(), Verticies.size() * sizeof(float));
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
		//#ifdef DEBUG
		//		//if (!uniform.second.dataInitialized) std::cout << "DebugInfo: Uniform " << uniform.second.name << " was nerver assigned";
		//#endif // DEBUG

		auto& data = UniformData[uniform.second.name].data;
		switch (uniform.second.type)
		{
		case UniformType::Int:
			m_Shader->UploadUniformInt(uniform.second.name, data.Int1);

			break;
		case UniformType::Float:
			m_Shader->UploadUniformFloat(uniform.second.name, data.Float1);
			break;
		case UniformType::Float2:
			m_Shader->UploadUniformFloat2(uniform.second.name, data.Float2);

			break;
		case UniformType::Float3:
			m_Shader->UploadUniformFloat3(uniform.second.name, data.Float3);

			break;
		case UniformType::Float4:
			m_Shader->UploadUniformFloat4(uniform.second.name, data.Float4);

			break;
		case UniformType::Mat4:
			m_Shader->UploadUniformMat4(uniform.second.name, data.Mat4);

			break;
		default:
			std::cout << "Using a Uniform type for which uploading wasnt yet implemented. Uniform name :" << uniform.second.name << "\n";

			break;
		}
	}
}

bool Mesh::hasUniform(std::string name)
{
	
	return UniformData.contains(name);;
}
