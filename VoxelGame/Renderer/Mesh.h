#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <memory>
enum class MeshType {
	Indexed, Unindexed
};

class Mesh
{
public:
	Mesh(MeshType type = MeshType::Unindexed);
	//~Mesh() {NrOfMeshes-=1; }
	MeshType getType() { return m_Type; }
	VertexArray& GetVertexArray() { return *m_VertexArray.get(); }
	std::shared_ptr<Shader>& getShader() { return m_Shader; }
	std::map<std::string, Uniform>& GetUniformData() { return UniformData; }

	unsigned int getCount();
	void Bind();
	void SetTexture(Texture* texture) { m_Texture.reset(texture); };
	void SetTexture(std::shared_ptr<Texture> texture) { m_Texture = texture; };
	void UpdateObjectsOnGPU();
	void SetShader( Shader* shader) { m_Shader.reset(shader); };
	void SetShader(std::shared_ptr<Shader>& shader) { m_Shader = shader; };
	 void PreDraw();
	void AddUniform(std::string name, UniformType type);
	void updateUniform(std::string name, UniformDataUnion data);
	void UploadAllUniforms();
	bool hasUniform(std::string name);
	bool hasTexture = false;
	std::vector<float> Verticies;
	std::vector<unsigned int> Indicies;
private:
	std::map<std::string, Uniform> UniformData;
	std::shared_ptr < VertexArray> m_VertexArray;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;
	MeshType m_Type;
	static  int NrOfMeshes;
};