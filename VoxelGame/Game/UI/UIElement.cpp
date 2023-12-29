#include "UIElement.h"
#include "../Game.h"
std::shared_ptr<Shader> UIElement::UIShader;

UIElement::UIElement(glm::vec2 Coords, glm::vec2 Size, glm::mat4 TransformMatrix) 
	: coords(Coords), size(Size), transformMatrix(TransformMatrix), mesh(MeshType::Indexed)
{

	glm::vec4 screenSpaceCoords_ = glm::vec4(coords, 0.f, 1.f);
	screenSpaceCoords = transformMatrix * screenSpaceCoords_;

	UIElementLayout = {
	{ShaderDataType::Float2,"aPos"},
	{ShaderDataType::Float2,"aTexCoordsOffset"},

	};
	mesh.AddUniform("itemAtlas", UniformType::Int);
	mesh.AddUniform("TexCoords", UniformType::Float2);



	mesh.updateUniform("itemAtlas", 0);
	mesh.SetTexture(0, Game::ItemTextureAtlas);
	mesh.hasTexture = true;
}

