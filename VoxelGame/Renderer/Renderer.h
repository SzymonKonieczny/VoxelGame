#pragma once
#include "Window.h"
#include "RendererCommad.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Buffers.h"
#include "Shader.h"


#include <iostream>
class Renderer {
public:
	
	static void Init();
	static void Shutdown();

	static void OnWindowResize(uint32_t width, uint32_t height);

	static void BeginScene(Camera& camera);
	static void EndScene();

	static void Submit();//MeshIndexed
//	static void Submit();//MeshUnindexed

	
	static Window window;
	
private:
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};
};