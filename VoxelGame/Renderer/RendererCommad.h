#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"
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

	static void DrawNotIndexed(Mesh& mesh)//Mesh
	{
		mesh.Bind();
		if (mesh.getShader()->GetUniformLocation("ModelMatrix") != -1)
		{
			mesh.getShader()->UploadUniformMat4("ModelMatrix", mesh.ModelMatrix);
		}
		if (mesh.getShader()->GetUniformLocation("CamViewMatrix") != -1)
		{
			mesh.getShader()->UploadUniformMat4("CamViewMatrix", Renderer::ViewProjectionMatrix);
		}
		glDrawArrays(GL_TRIANGLES, 0, mesh.getCount());

	}

};