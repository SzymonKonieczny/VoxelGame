#include "Mesh.h"
#include <iostream>
 int Mesh::NrOfMeshes = 0;
Mesh::Mesh(MeshType type)
{
	m_VertexArray.reset(new VertexArray());
	m_Type = type;
	m_VertexArray->SetVertexBuffer(new VertexBuffer());
	if (type == MeshType::Indexed)
	{
		m_VertexArray->SetIndexBuffer(new IndexBuffer());
	}

	//DEBUG STUFF
	//NrOfMeshes += 1;
	//std::cout << "Mesh constructed "<< NrOfMeshes <<"\n";
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



	//Very bad for performance, very temporary
	//Do it so that it only updates them if theres been a change to the Verticies vector
	//UpdateObjectsOnGPU();
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
	glFlush();
	Verticies.clear();
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
		uploadSingleUniform(uniform.first);
		//auto& data = UniformData[uniform.second.name].data;
		//switch (uniform.second.type)
		//{
		//case UniformType::Int:
		//	m_Shader->UploadUniformInt(uniform.second.name, data.Int1);
		//
		//	break;
		//case UniformType::Float:
		//	m_Shader->UploadUniformFloat(uniform.second.name, data.Float1);
		//	break;
		//case UniformType::Float2:
		//	m_Shader->UploadUniformFloat2(uniform.second.name, data.Float2);
		//
		//	break;
		//case UniformType::Float3:
		//	m_Shader->UploadUniformFloat3(uniform.second.name, data.Float3);
		//
		//	break;
		//case UniformType::Float4:
		//	m_Shader->UploadUniformFloat4(uniform.second.name, data.Float4);
		//
		//	break;
		//case UniformType::Mat4:
		//	m_Shader->UploadUniformMat4(uniform.second.name, data.Mat4);
		//
		//	break;
		//default:
		//	std::cout << "Using a Uniform type for which uploading wasnt yet implemented. Uniform name :" << uniform.second.name << "\n";
		//
		//	break;
		//}
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
