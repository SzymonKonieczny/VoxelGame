#pragma once
#include <glm/glm.hpp>
#include "../Renderer/Mesh.h"
#include <iostream>

class RendererCommand {

public:
	static void Init()
	{

	}
	static void BindDefaultFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
			
	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);

	}

	static void SetClearColor(const glm::vec4& color)
	{

	}

	static void Clear()
	{

	}

	static void DrawIndexed(Mesh& mesh)//Mesh
	{
		glDrawElements(GL_TRIANGLES,mesh.GetVertexArray().GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,0);

	}

	static void DrawNotIndexed(Mesh& mesh)//Mesh
	{


		glDrawArrays(GL_TRIANGLES, 0, mesh.getCount());

	}

};