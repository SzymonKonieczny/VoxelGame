#pragma once
#include "../Renderer/Window.h"
#include "../Renderer/RendererCommad.h"
#include "../Renderer/Camera.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/Buffers.h"
#include "../Renderer/Shader.h"


#include <iostream>
class Renderer {
public:
	
	static void Init();
	static void Shutdown();

	static void OnWindowResize(GLFWwindow* window, int width, int height);

	static void BeginScene(Camera& camera);
	static void EndScene();

	static void Submit();//MeshIndexed
//	static void Submit();//MeshUnindexed

	
	static Window window;
	
private:
	
	static glm::mat4 ViewProjectionMatrix;
	
};