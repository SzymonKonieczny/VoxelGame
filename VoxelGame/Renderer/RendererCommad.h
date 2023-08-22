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
	}

	static void DrawNotIndexed(Mesh& mesh, glm::mat4 ViewProjectionMatrix)//Mesh
	{
		mesh.Bind();
		if (mesh.hasUniform("viewProjMatrix")) mesh.updateUniform("viewProjMatrix", ViewProjectionMatrix);
		mesh.PreDraw();
		GLenum err = glGetError();

		glDrawArrays(GL_TRIANGLES, 0, mesh.getCount());
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "/n" << err << "/n";
		}
	}

};