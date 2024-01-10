#pragma once

#include "../../Renderer/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class UIElement {
public:
	Mesh mesh;

	static std::shared_ptr<Shader> UIShader;
	std::vector<std::shared_ptr<UIElement>> Children;

	glm::vec2 screenSpaceCoords; 

	glm::vec2 coords; //start Coords
	glm::vec2 size; //Span on X, span on Y
	glm::mat4 transformMatrix;
	BufferLayout UIElementLayout;
	UIElement(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix);
	virtual void Update() = 0;

	void UpdateTransformation(glm::mat4 TransformMatrix)
	{
		transformMatrix = TransformMatrix;
		mesh.updateUniform("modelMatrix", transformMatrix);

		glm::vec4 screenSpaceCoords_ = glm::vec4(coords, 0.f, 1.f);
		screenSpaceCoords = transformMatrix * screenSpaceCoords_;


		glm::mat4 childModelMat = transformMatrix;
		childModelMat = glm::translate(childModelMat, glm::vec3(coords.x, coords.y, 1));
		childModelMat = glm::scale(childModelMat, glm::vec3(size.x, size.y, 1));
		for (auto& UI : Children)
		{
			UI->UpdateTransformation(childModelMat);
		}
	}
	std::vector<Mesh*> GetMeshesWithChildren() {
		std::vector<Mesh*> queue;
		queue.push_back(&mesh);
		for (auto& c : Children)
		{
			for (auto& UIELEMENT : c->GetMeshesWithChildren())

				queue.push_back(UIELEMENT);
		}

		return queue;
	}
	struct UIElementVertex {
		glm::vec2 Pos;
		glm::vec2 aTexCoords;


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
