#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <vector>

#include <memory>
enum class MeshType {
	Indexed, Unindexed
};

class Mesh
{
public:
	Mesh(MeshType type = MeshType::Unindexed);
	MeshType getType() { return Type; }
	unsigned int getCount();
	std::vector<float> Verticies;
	std::vector<unsigned int> Indicies;
	void Bind();
	void UpdateGLObjs();
	void SetShader( Shader* shader) { Shader.reset(shader); };
	void SetShader(std::shared_ptr<Shader> shader) { Shader = shader; };


	VertexArray VertexArray;
private:
	std::shared_ptr<Shader> Shader;
	std::shared_ptr<Texture> Texture;
	bool hasTexture = false;
	MeshType Type;
};