#pragma once
#include "UIElement.h"
#include "UIItemIcon.h"
#include <glm/glm.hpp>
#include "../IInventory.h"
#include "../ItemInfo.h"
class HUDUI : public UIElement, public IInventory
{
public:
	virtual void Update() override
	{
	
		
		Children[0]->Update();
		//for (auto& c : Children)
		//{
		//	c->Update();
		//}
	}
	HUDUI(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix) : UIElement (Coords, Size, TransformMatrix)
	{

		ItemStacks.resize(7);
		std::fill(ItemStacks.begin(), ItemStacks.end(), ItemStack(1,0));

		mesh.SetShader(UIElement::UIShader);

		mesh.AddUniform("modelMatrix", UniformType::Mat4);
		mesh.updateUniform("modelMatrix", TransformMatrix);
		mesh.GetVertexArray().SetLayout(UIElementLayout);

		mesh.updateUniform("TexCoords", glm::vec2(0.6f, 0.9f));


		float TxtAtlassoffset = 0.1f;

		UIElementVertex v;
		v = UIElementVertex(coords, glm::vec2(0.f, 0.f)); // 0,0
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + glm::vec2(0.f, Size.y), glm::vec2(0.f, TxtAtlassoffset)); // 0, 1
		pushVertToMesh(mesh, v);
		v = UIElementVertex(coords + Size, glm::vec2(TxtAtlassoffset*4, TxtAtlassoffset)); // 1, 1
		pushVertToMesh(mesh, v);

		v = UIElementVertex(coords + glm::vec2(Size.x, 0.f), glm::vec2(TxtAtlassoffset*4, 0.f)); // 1, 0
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
	void setHighlight(int ItemstackNr)
	{
		glm::mat4 childModelMat = transformMatrix;
		childModelMat = glm::translate(childModelMat, glm::vec3(coords.x, coords.y, 1));
		childModelMat = glm::scale(childModelMat, glm::vec3(size.x, size.y, 1));
		Children[Children.size()-1 ]->UpdateTransformation(glm::translate(childModelMat, glm::vec3(1/7.f * ItemstackNr,0,0)));
	}
	void setItemStack(int ItemstackNr, ItemStack itemStack)
	{
		ItemStacks[ItemstackNr] = itemStack;
		Children[ItemstackNr]->mesh.updateUniform("TexCoords", ItemTable[itemStack.ID].UV);
	}
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
		Children.emplace_back((new UIItemIcon(glm::vec2(0.f, 0.0f), glm::vec2(0.1125f, 0.9f), childModelMat)));
		Children[Children.size()-1]->mesh.updateUniform("TexCoords", glm::vec2(0.5f, 0.9f));
	}

};
