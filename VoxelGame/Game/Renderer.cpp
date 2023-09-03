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
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, ShadowMapRes, ShadowMapRes);// Shadow render pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::vec3 lightPos = glm::vec3(0.5f, 20.0f, 0.8f);
	glm::mat4 lightProjection = glm::ortho(-ShadowMapRes/2.0f, ShadowMapRes / 2.0f, -ShadowMapRes / 2.0f, ShadowMapRes / 2.0f, 0.1f, 100.0f);

		/*glm::mat4 lightView = glm::lookAt(glm::vec3(-60.f, 21.0f, -5.f),
		glm::vec3(1.f, -1.0f, 1.f),
		glm::vec3(0.0f, 1.0f, 0.0f));*/

	//glm::mat4 lightProjection = glm::perspective(glm::radians(90.f),1.f,0.1f,1000.f);

		glm::mat4 lightView = glm::lookAt(lightPos, //position
			lightPos + glm::normalize(glm::vec3(0.8f, -0.4f, 0.75f)), //position + direction
	glm::vec3(0.0f, 1.0f, 0.0f)); //41.f, 63.0f, -17.f
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	//for (auto& m : Meshes)
	//{
	//	m->Bind();
	//	if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", lightSpaceMatrix);
	//	if (m->hasUniform("modelMatrix")) m->updateUniform("modelMatrix", m->GetUniformData()["modelMatrix"].data);
	//
	//
	//	m->PreDraw();
	//	switch (m->getType())
	//	{
	//	case MeshType::Indexed:
	//		RendererCommand::DrawIndexed(*m);
	//		break;
	//	case MeshType::Unindexed:
	//
	//		RendererCommand::DrawNotIndexed(*m);
	//		break;
	//	}
	//}

	frame->Bind();
	glViewport(0, 0, screenWidth, screenHeight); // Normal render pass
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE7);	//ShadowMap uploading 
	ShadowMap->BindDepthTexture();
	//int MeshesSize = 0;
	for (auto& m : Meshes)
	{
		m->Bind();
		if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", ViewProjectionMatrix);
		if (m->hasUniform("shadowDepthTexture")) m->updateUniform("shadowDepthTexture", 7);
		if (m->hasUniform("lightSpaceMatrix")) m->updateUniform("lightSpaceMatrix", lightSpaceMatrix);

		if (m->hasUniform("viewPos")) m->updateUniform("viewPos", CameraPos);
		if (m->hasUniform("lightPos")) m->updateUniform("lightPos", lightPos);
		m->PreDraw();
		break;
	}
	for (auto& m : Meshes)
	{
		//MeshesSize += 1;

		
		m->Bind();
		//if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", ViewProjectionMatrix);
		//if (m->hasUniform("shadowDepthTexture")) m->updateUniform("shadowDepthTexture", 7);
		//if (m->hasUniform("lightSpaceMatrix")) m->updateUniform("lightSpaceMatrix", lightSpaceMatrix);
		//
		//if (m->hasUniform("viewPos")) m->updateUniform("viewPos", CameraPos);
		//if (m->hasUniform("lightPos")) m->updateUniform("lightPos", lightPos);
			
		if (m->hasUniform("modelMatrix")) m->updateUniform("modelMatrix", m->GetUniformData()["modelMatrix"].data);
		
		m->uploadSingleUniform("modelMatrix");
		
		//m->PreDraw();
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
	//std::cout << MeshesSize << "  meshes rendered this frame \n";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT );

	ScreenQuad->Bind();
	frame->BindColorTexture();

	ScreenQuad->PreDraw();
	RendererCommand::DrawNotIndexed(*ScreenQuad);

	Meshes.clear();


}

void Renderer::Submit(Mesh& m)
{
	Meshes.push_back(&m);
}
