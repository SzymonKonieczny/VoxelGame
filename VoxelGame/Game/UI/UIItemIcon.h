#pragma once
#include "UIElement.h"
class UIItemIcon : public UIElement{

public:
	UIItemIcon(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix) :
		UIElement(Coords, Size, TransformMatrix)
	{
	
		mesh.SetShader(UIElement::UIShader);

		mesh.AddUniform("modelMatrix", UniformType::Mat4);
		mesh.updateUniform("modelMatrix", TransformMatrix);
		mesh.GetVertexArray().SetLayout(UIElementLayout);

		UIElementVertex v;
		v = UIElementVertex(coords, glm::vec2(1.f, 1.f));
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + glm::vec2(0.f, Size.y), glm::vec2(1.f, 1.f));
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + Size, glm::vec2(1.f, 1.f));
		pushVertToMesh(mesh, v);

		v = UIElementVertex(coords + glm::vec2(Size.x, 0.f), glm::vec2(1.f, 1.f));
		pushVertToMesh(mesh, v);

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(1);
		mesh.Indicies.push_back(2);

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(2);
		mesh.Indicies.push_back(3);

		mesh.UpdateObjectsOnGPU();

	}
	// Inherited via UIElement
};