#include "Renderer.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Renderer::CameraPos;
glm::vec3 Renderer::CameraRot;
Window Renderer::window; //constructor static call
glm::mat4 Renderer::ViewProjectionMatrix;
std::list<Mesh*> Renderer::Meshes;
std::unique_ptr<Framebuffer> frame;//(FramebufferOptions(screenWidth,screenHeight )); //Width, Height
std::unique_ptr < Mesh> ScreenQuad;
std::unique_ptr<Framebuffer> ShadowMap;//(FramebufferOptions(screenWidth,screenHeight )); //Width, Height
int ShadowMapRes = 1024;
void Renderer::Init()
{
	window.Init();
	
	glfwSetWindowSizeCallback(window.GetHandle(), OnWindowResize);
	RendererCommand::SetViewport(0, 0, screenWidth,screenHeight);

	frame.reset(new Framebuffer(FramebufferOptions(screenWidth, screenHeight)));
	ShadowMap.reset(new Framebuffer(FramebufferOptions(screenWidth, screenHeight,false)));

	ScreenQuad.reset(new Mesh);

	ScreenQuad->GetVertexArray().SetVertexBuffer(new VertexBuffer());
	ScreenQuad->Verticies = {
		// Coords    // texCoords
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,
	
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

	ScreenQuad->GetVertexArray().SetLayout(BufferLayout({ { ShaderDataType::Float2,"Coords"},{ShaderDataType::Float2,"texCoords" }}));
	ScreenQuad->UpdateObjectsOnGPU();
	ScreenQuad->SetShader(new Shader("Game/Shaders/ScreenQuadShader.vert", "Game/Shaders/ScreenQuadShader.frag"));
	ScreenQuad->AddUniform("screenTexture", UniformType::Int);  
	ScreenQuad->AddUniform("depthTexture", UniformType::Int);

	ScreenQuad->AddUniform("lightSpaceMatrix", UniformType::Mat4);

	ScreenQuad->updateUniform("screenTexture", 0);
	ScreenQuad->updateUniform("depthTexture", 1);



}

void Renderer::Shutdown()
{
	window.Shutdown();
}

void Renderer::OnWindowResize(GLFWwindow* window, int width, int height)
{
	screenHeight = height;
	screenWidth = width;
	RendererCommand::SetViewport(0, 0, screenWidth, screenHeight);

}

void Renderer::BeginScene(Camera& camera) // argument : vec<ligtsources>
{
	ViewProjectionMatrix =  camera.GetProjectionMatrix()* camera.GetViewMatrix();
	CameraPos = camera.GetPosition();
	CameraRot = camera.GetRotation();
}

void Renderer::EndScene()
{
	ShadowMap->Bind();
	glViewport(0, 0, ShadowMapRes, ShadowMapRes);// Shadow render pass
	glClear(GL_DEPTH_BUFFER_BIT);
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
	glm::mat4 lightView = glm::lookAt(/*CameraPos + */ glm::vec3(-5.f, 50.0f, 0.f),
		glm::vec3(0.f, 0.0f, 0.f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	for (auto& m : Meshes)
	{
		m->Bind();
		if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", lightSpaceMatrix);
		m->PreDraw();
		switch (m->getType())
		{
		case MeshType::Indexed:
			RendererCommand::DrawIndexed(*m);
			break;
		case MeshType::Unindexed:

			RendererCommand::DrawNotIndexed(*m);
			break;
		}
	}

	frame->Bind();
	glViewport(0, 0, screenWidth, screenHeight); // Normal render pass
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& m : Meshes)
	{
		m->Bind();
		if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", ViewProjectionMatrix);
		m->PreDraw();
		switch (m->getType())
		{
		case MeshType::Indexed:
			RendererCommand::DrawIndexed(*m);
			break;
		case MeshType::Unindexed:
			
			RendererCommand::DrawNotIndexed(*m);
			break;
		}
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT );

	ScreenQuad->Bind();
	frame->BindColorTexture();
	//ShadowMap->BindDepthTexture();
	ScreenQuad->PreDraw();
	RendererCommand::DrawNotIndexed(*ScreenQuad);

	Meshes.clear();


}

void Renderer::Submit(Mesh& m)
{
	Meshes.push_back(&m);
}
