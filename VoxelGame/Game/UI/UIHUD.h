#pragma once
#include "UIElement.h"
class HUDUI : public UIElement
{
public:
	glm::vec2 coords; //start Coords
	glm::vec2 size; //Span on X, span on Y
	std::vector<UIElement> Children;
	//HUDUI(glm::vec2 Coords, glm::vec2 Size) : coords(Coords), size(Size) 
	HUDUI() : Mesh(MeshType::Indexed)
	{
		Mesh.SetShader(UIElement::UIShader);

		BufferLayout UIElementLayout = {
		{ShaderDataType::Float2,"aPos"},
		};

		Mesh.GetVertexArray().SetLayout(UIElementLayout);
		//Mesh.AddUniform("aPos", UniformType::Float2);


		UIElementVertex v;
		v = UIElementVertex(glm::vec2(-0.5f, 0.5f));
		pushVertToMesh(Mesh, v);
		v = UIElementVertex(glm::vec2(0.5f, 0.5f));
		pushVertToMesh(Mesh, v);
		v = UIElementVertex(glm::vec2(-0.5f, -0.5f));
		pushVertToMesh(Mesh, v);
		v = UIElementVertex(glm::vec2(0.5f, -0.5f));
		pushVertToMesh(Mesh, v);

		Mesh.Indicies.push_back(0);
		Mesh.Indicies.push_back(1);
		Mesh.Indicies.push_back(2);

		Mesh.Indicies.push_back(2);
		Mesh.Indicies.push_back(3);
		Mesh.Indicies.push_back(1);

		Mesh.UpdateObjectsOnGPU();
	}
	

	// Inherited via UIElement
	virtual Mesh& GetMesh() override;

	virtual Mesh& GetMeshesWithChildren() override;
private:
	Mesh Mesh;

};
