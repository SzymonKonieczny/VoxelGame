#pragma once

#include "../../Renderer/Mesh.h"
#include <glm/glm.hpp>

class UIElement {
public:
	static std::shared_ptr<Shader> UIShader;

	virtual Mesh* GetMesh() = 0;
	virtual Mesh* GetMeshesWithChildren() = 0;
	struct UIElementVertex {
		glm::vec2 Pos;

	};
	static void pushVertToMesh(Mesh& mesh, UIElementVertex& vert)
	{
		float* ptr = (float*)&vert;

		for (int i = 0; i < sizeof(UIElementVertex) / sizeof(float); i++)
		{
			mesh.Verticies.push_back(*ptr);
			ptr += 1;
		}
	}
};
std::shared_ptr<Shader> UIElement::UIShader;