#pragma once
#include "UIElement.h"
#include "UIItemIcon.h"
#include <glm/glm.hpp>
#include "../IInventory.h"
#include <functional>
#include <memory>
class Player;
class UIPlayerInventory : public UIElement, public IInventory
{
public:
	virtual void Update() override
	{
		for (auto& c : Children)
		{
			c->Update();
		}
	}
	UIPlayerInventory(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix) : UIElement(Coords, Size, TransformMatrix)
	{

		ItemStacks.resize(25);
		std::fill(ItemStacks.begin(), ItemStacks.end(), ItemStack(1, 0));

		mesh.SetShader(UIElement::UIShader);

		mesh.AddUniform("modelMatrix", UniformType::Mat4);
		mesh.updateUniform("modelMatrix", TransformMatrix);
		mesh.GetVertexArray().SetLayout(UIElementLayout);

		mesh.updateUniform("TexCoords", glm::vec2(0.5f, 0.4f));


		float TxtAtlassoffset = 0.5f;

		UIElementVertex v;
		v = UIElementVertex(coords, glm::vec2(0.f, 0.f)); // 0,0
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + glm::vec2(0.f, Size.y), glm::vec2(0.f, TxtAtlassoffset)); // 0, 1
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + Size, glm::vec2(TxtAtlassoffset , TxtAtlassoffset)); // 1, 1
		pushVertToMesh(mesh, v);

		v = UIElementVertex(coords + glm::vec2(Size.x, 0.f), glm::vec2(TxtAtlassoffset, 0.f)); // 1, 0
		pushVertToMesh(mesh, v);

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(1);
		mesh.Indicies.push_back(2);

		mesh.Indicies.push_back(0);
		mesh.Indicies.push_back(2);
		mesh.Indicies.push_back(3);

		mesh.UpdateObjectsOnGPU();


		PopulateInvenory();
	}
	std::function<void(int)> SetHUDItem;
private:

	void PopulateInvenory() {
		glm::mat4 childModelMat = transformMatrix;
		childModelMat = glm::translate(childModelMat, glm::vec3(coords.x, coords.y, 1));
		childModelMat = glm::scale(childModelMat, glm::vec3(size.x, size.y, 1));
		int iter = 0;
		for (int i = 0; i < 5; i++)
		{
			if (iter >= ItemTable.size()) break;

			for (int k = 0; k < 5; k++)
			{
				iter += 1;
				if (iter >= ItemTable.size()) break;

				Children.emplace_back((new UIItemIcon(glm::vec2(0.2f * k, 0.2f*i), glm::vec2(0.2f, 0.2f), childModelMat)));
				auto ptr = std::dynamic_pointer_cast<UIItemIcon>(Children[Children.size() - 1]);
				ptr->LeftClickCallback = [iter,this]() { SetHUDItem(iter); };
				
				ptr->mesh.updateUniform("TexCoords", ItemTable[iter].UV);


			}

		}

	}
};