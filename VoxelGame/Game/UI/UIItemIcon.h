#pragma once
#include "UIElement.h"
#include "../Input.h"
class UIItemIcon : public UIElement{

public:
	UIItemIcon(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix) :
		UIElement(Coords, Size, TransformMatrix)
	{
	
		mesh.SetShader(UIElement::UIShader);

		mesh.AddUniform("modelMatrix", UniformType::Mat4);

		mesh.updateUniform("modelMatrix", TransformMatrix);
		mesh.GetVertexArray().SetLayout(UIElementLayout);
		float TxtAtlassoffset = 0.1f;

		UIElementVertex v;
		v = UIElementVertex(coords, glm::vec2(0.f, 0.f)); // 0,0
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + glm::vec2(0.f, Size.y), glm::vec2(0.f, TxtAtlassoffset)); // 0, 1
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + Size, glm::vec2(TxtAtlassoffset, TxtAtlassoffset)); // 1, 1
		pushVertToMesh(mesh, v);

		v = UIElementVertex(coords + glm::vec2(Size.x, 0.f), glm::vec2(TxtAtlassoffset, 0.f)); // 1, 0
		pushVertToMesh(mesh, v);

		mesh.Indicies.push_back(0); 
		mesh.Indicies.push_back(1); 
		mesh.Indicies.push_back(2); 

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(2);
		mesh.Indicies.push_back(3);

		mesh.updateUniform("TexCoords", glm::vec2(0.0f, 0.f));


		mesh.UpdateObjectsOnGPU();

	}
	virtual void Update() override
	{
		double mouseX, mouseY;
		Input::getMousePosNormalized(&mouseX, &mouseY);
		//mouseX = mouseX * 2 - 1;
		//mouseY = mouseY * 2 - 1;

		glm::vec4 screenSpaceCoords(coords, 0.f, 0.f);
		glm::vec4 screenSpaceSize(size, 0.f, 0.f);

		screenSpaceCoords=	screenSpaceCoords * transformMatrix;
		screenSpaceSize =	screenSpaceSize * transformMatrix;
		if (mouseY < screenSpaceCoords.y + screenSpaceSize.y &&
			mouseY > screenSpaceCoords.y)
			std::cout << "In\n";
		else std::cout << "Out\n";



	}
	// Inherited via UIElement
};