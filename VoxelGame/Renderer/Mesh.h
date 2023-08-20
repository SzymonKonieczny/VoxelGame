#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>

#include <memory>
enum class MeshType {
	Indexed, Unindexed
};

class Mesh
{
public:
	Mesh(MeshType type = MeshType::Unindexed);
	MeshType getType() { return m_Type; }
	unsigned int getCount();
	std::vector<float> Verticies;
	std::vector<unsigned int> Indicies;
	void Bind();
	void UpdateGLObjs();
	void SetShader( Shader* shader) { m_Shader.reset(shader); };
	void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; };
	glm::mat4 ModelMatrix;
	VertexArray& GetVertexArray() { return *m_VertexArray.get(); }
	std::shared_ptr<Shader>& getShader() { return m_Shader; }
private:

	std::shared_ptr < VertexArray> m_VertexArray;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;
	bool hasTexture = false;
	MeshType m_Type;
};