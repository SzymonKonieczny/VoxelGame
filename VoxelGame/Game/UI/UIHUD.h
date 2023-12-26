#pragma once
#include "UIElement.h"
#include "UIItemIcon.h"
#include <glm/glm.hpp>

class HUDUI : public UIElement
{
public:
	
	HUDUI(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix) : UIElement (Coords, Size, TransformMatrix)
	{

		mesh.SetShader(UIElement::UIShader);

		mesh.AddUniform("modelMatrix", UniformType::Mat4);
		mesh.updateUniform("modelMatrix", TransformMatrix);
		mesh.GetVertexArray().SetLayout(UIElementLayout);


		UIElementVertex v;
		v = UIElementVertex(coords , glm::vec2(0.f, 0.f));
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + glm::vec2(0.f, Size.y), glm::vec2(0.f, 0.f));
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + Size, glm::vec2(0.f, 0.f));
		pushVertToMesh(mesh, v);

		v = UIElementVertex(coords + glm::vec2(Size.x, 0.f), glm::vec2(0.f, 0.f));
		pushVertToMesh(mesh, v);

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(1);
		mesh.Indicies.push_back(2);

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(2);
		mesh.Indicies.push_back(3);

		mesh.UpdateObjectsOnGPU();
		PopulateHUD();
	}
	

	// Inherited via UIElement

private:
	void PopulateHUD() {
		glm::mat4 childModelMat = transformMatrix;
		childModelMat = glm::translate(childModelMat, glm::vec3(coords.x, coords.y, 1));
		childModelMat = glm::scale(childModelMat, glm::vec3(size.x, size.y, 1));
		float iter = 0.1f;
		for (int i = 0; i < 8; i++)
		{
			Children.emplace_back( ( new UIItemIcon(glm::vec2(0.12f * iter, 0.05f), glm::vec2(0.1125f, 0.9f), childModelMat)));
			iter += 1;
		}
	}

};
