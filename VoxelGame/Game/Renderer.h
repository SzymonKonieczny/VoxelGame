#pragma once
#include "../Renderer/Window.h"
#include "../Renderer/RendererCommad.h"
#include "../Renderer/Camera.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/Buffers.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Framebuffer.h"

#include <list>
#include <iostream>
class Renderer {
public:
	
	static void Init();
	static void Shutdown();

	static void OnWindowResize(GLFWwindow* window, int width, int height);

	static void BeginScene(Camera& camera);
	static void RenderChunks();
	static void RenderGeneralMeshes();
	static void RenderUI();

	static void EndScene();

	static void SubmitChunk(Mesh& m);//MeshIndexed
	static void SubmitGeneral(Mesh& m);//MeshIndexed
	static void SubmitUI(Mesh& m);//MeshIndexed


	
	static Window window;
	
	static glm::mat4 ViewProjectionMatrix;
	static glm::vec3 CameraPos;
	static glm::vec3 CameraRot;

private:
	static std::list<Mesh*> ChunkMeshes;
	static std::list<Mesh*> GeneralMeshes;
	static std::list<Mesh*> UIMeshes;


};