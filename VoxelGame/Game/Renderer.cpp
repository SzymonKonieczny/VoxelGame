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
std::unique_ptr < Shader> ShadowPassShader;
std::unique_ptr<Framebuffer> ShadowMap;//(FramebufferOptions(screenWidth,screenHeight )); //Width, Height
int ShadowMapRes = 1024;
glm::vec3 lightPos = glm::vec3(0.5f, 20.0f, 0.8f);
glm::vec3 lightDir = glm::vec3(0.8f, -0.4f, 0.75f);

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

	ShadowPassShader.reset(new Shader("Game/Shaders/ShadowPass.vert", "Game/Shaders/ShadowPass.frag"));
}

void Renderer::Shutdown()
{
	window.Shutdown();
}

void Renderer::OnWindowResize(GLFWwindow* window, int width, int height)
{
	screenHeight = height;
	screenWidth = width;
	frame.reset(new Framebuffer(FramebufferOptions(screenWidth, screenHeight)));
	ShadowMap.reset(new Framebuffer(FramebufferOptions(screenWidth, screenHeight, false)));


}

void Renderer::BeginScene(Camera& camera) // argument : vec<ligtsources>
{
	ViewProjectionMatrix =  camera.GetProjectionMatrix()* camera.GetViewMatrix();
	CameraPos = camera.GetPosition();
	CameraRot = camera.GetRotation();
}

void Renderer::EndScene()
{

	glm::mat4 lightProjection = glm::ortho((float)-100, (float)100, (float)-100, (float)100, 0.1f, 1000.0f);

		/*glm::mat4 lightView = glm::lookAt(glm::vec3(-60.f, 21.0f, -5.f),
		glm::vec3(1.f, -1.0f, 1.f),
		glm::vec3(0.0f, 1.0f, 0.0f));*/

	//glm::mat4 lightProjection = glm::perspective(glm::radians(90.f), screenWidth / (float)screenHeight,0.1f,100.f);

		glm::mat4 lightView = glm::lookAt(lightPos, //position
			lightPos + glm::normalize(lightDir), //position + direction
	glm::vec3(0.0f, 1.0f, 0.0f)); //41.f, 63.0f, -17.f
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	if (Input::isPressed(GLFW_KEY_0))
	{
		lightPos = CameraPos;
		lightDir = CameraRot;
		std::cout << "Teleporting the lightsource to player ...\n";
	}

#if 0 // Shadowmap render	
	ShadowMap->Bind();


	glViewport(0, 0, ShadowMapRes, ShadowMapRes);// Shadow render pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ShadowPassShader->Bind();
	ShadowPassShader->UploadUniformMat4("lightSpaceMatrix", lightSpaceMatrix);

	for (auto& m : Meshes)
	{
		if (m->getCount() == 0) continue;
		if (!m->getReadyForDraw()) continue;

		m->Bind();
		ShadowPassShader->Bind();
		ShadowPassShader->UploadUniformMat4("modelMatrix", m->GetUniformData().at("modelMatrix").data.Mat4);
	
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
#endif
	frame->Bind();
	glViewport(0, 0, screenWidth, screenHeight); // Normal render pass
	glClearColor(0.39f, 0.67f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE7);	//ShadowMap uploading, binding slot 7
		ShadowMap->BindDepthTexture(); // uploading to slot 7

	for (auto& m : Meshes)
	{
		if (m->getCount() == 0) continue;

		if (!m->getReadyForDraw()) continue;

		m->Bind();
		if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", ViewProjectionMatrix);
		if (m->hasUniform("shadowDepthTexture")) m->updateUniform("shadowDepthTexture", 7); // letting the shader know at which slot the shadowmapTexture is

		if (m->hasUniform("lightSpaceMatrix")) m->updateUniform("lightSpaceMatrix", lightSpaceMatrix);

		m->PreDraw();
		break;
	}
	for (auto& m : Meshes)
	{
		if (!m->getReadyForDraw()) continue;
		m->Bind();
				
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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight); // ScreenQuad draw

	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT );

	ScreenQuad->Bind();
	frame->BindColorTexture();

	ScreenQuad->PreDraw();
	RendererCommand::DrawNotIndexed(*ScreenQuad);
	glEnable(GL_DEPTH_TEST);
	Meshes.clear();


}

void Renderer::Submit(Mesh& m)
{
	Meshes.push_back(&m); //Break it up to ChunkMeshes, and other meshes to keep  i made optimalizations later on
}
