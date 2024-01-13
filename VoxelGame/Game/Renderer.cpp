#include "Renderer.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Renderer::CameraPos;
glm::vec3 Renderer::CameraRot;
Window Renderer::window; //constructor static call
glm::mat4 Renderer::ViewProjectionMatrix;
std::list<Mesh*> Renderer::ChunkMeshes;
 std::list<Mesh*> Renderer::GeneralMeshes;
 std::list<Mesh*> Renderer::UIMeshes;
std::unique_ptr<Framebuffer> frame;//(FramebufferOptions(screenWidth,screenHeight )); //Width, Height
std::unique_ptr < Mesh> ScreenQuad;
std::unique_ptr < Shader> ShadowPassShader;
std::unique_ptr<Framebuffer> ShadowMap;//(FramebufferOptions(screenWidth,screenHeight )); //Width, Height
int ShadowMapRes = 1000;
glm::vec3 lightPos = glm::vec3(2000, 200, 2000);
glm::vec3 lightDir = glm::vec3(0.f, -1.4f,0.f);

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
	WindowResized = true; // only for UI scaling

}

void Renderer::BeginScene(Camera& camera) // argument : vec<ligtsources>
{
	ViewProjectionMatrix =  camera.GetProjectionMatrix()* camera.GetViewMatrix();
	CameraPos = camera.GetPosition();
	CameraRot = camera.GetRotation();
}

void Renderer::RenderChunks()
{

	glm::mat4 lightProjection = glm::ortho((float)-500, (float)500, (float)-500, (float)500, 0.1f, 200.0f);


	if (Input::isPressed(GLFW_KEY_0))
	{
		lightPos = CameraPos;
		lightDir = CameraRot;
		std::cout << "Teleporting the lightsource to player ...\n";
	}

		glm::mat4 lightView = glm::lookAt(lightPos, //position
				lightPos + glm::normalize(lightDir), //position + direction
					glm::vec3(0.0f, 1.0f, 0.0f)); //41.f, 63.0f, -17.f
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;



	if (!LightRendering)// Shadowmap render	
	{
		ShadowMap->Bind();

		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, ShadowMapRes, ShadowMapRes);// Shadow render pass
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ShadowPassShader->Bind();
		ShadowPassShader->UploadUniformMat4("lightSpaceMatrix", lightSpaceMatrix);

		for (auto& m : ChunkMeshes)
		{
			if (m->getCount() == 0) continue;

			if (!m->getReadyForDraw()) continue;

			m->Bind();
			ShadowPassShader->Bind();
			ShadowPassShader->UploadUniformMat4("modelMatrix", m->GetUniformData().at("modelMatrix").data.Mat4);
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
	}
	
	frame->Bind();
	glViewport(0, 0, screenWidth, screenHeight); // Normal render pass
	glClearColor(0.39f, 0.67f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE7);	//ShadowMap uploading, binding slot 7
		ShadowMap->BindDepthTexture(); // uploading to slot 7

	for (auto& m : ChunkMeshes)
	{

		if (!m->getReadyForDraw()) continue;

		m->Bind();
		if (m->hasUniform("viewProjMatrix")) m->updateUniform("viewProjMatrix", ViewProjectionMatrix);
		if (m->hasUniform("shadowDepthTexture")) m->updateUniform("shadowDepthTexture", 7); // letting the shader know at which slot the shadowmapTexture is

		if (m->hasUniform("lightSpaceMatrix")) m->updateUniform("lightSpaceMatrix", lightSpaceMatrix);

		m->PreDraw();
		break;
	}
	
	int nrMeshesDrawn = 0;
	for (auto& m : ChunkMeshes)
	{
		if (m->getCount() == 0) continue;
		if (!m->getReadyForDraw()) continue;
		nrMeshesDrawn += 1;
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
	
	ChunkMeshes.clear();
	//std::cout << "Number of drawn meshes " << nrMeshesDrawn << '\n';

}
void Renderer::EndScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

	RenderChunks();
	RenderGeneralMeshes();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight); // ScreenQuad draw

	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ScreenQuad->Bind();
	frame->BindColorTexture();

	if (renderShadowMap)
	{
		glActiveTexture(GL_TEXTURE0);	//ShadowMap uploading, binding slot 7
		ShadowMap->BindDepthTexture();
	}


	ScreenQuad->PreDraw();

	RendererCommand::DrawNotIndexed(*ScreenQuad);

	//glDisable(GL_CULL_FACE);

	RenderUI();
	glEnable(GL_DEPTH_TEST);
}
void Renderer::SubmitChunk(Mesh& m)
{
	ChunkMeshes.push_back(&m); //Break it up to ChunkMeshes, and other meshes to keep  i made optimalizations later on
}
void Renderer::SubmitGeneral(Mesh& m)
{
	GeneralMeshes.push_back(&m); //Break it up to ChunkMeshes, and other meshes to keep  i made optimalizations later on
}
void Renderer::SubmitUI(Mesh& m)
{
	UIMeshes.push_back(&m); //Break it up to ChunkMeshes, and other meshes to keep  i made optimalizations later on
}
void Renderer::RenderGeneralMeshes()
{

}
void Renderer::RenderUI()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, screenWidth, screenHeight);
	//We do not clear when drawin ui xd		glClearColor(0.39f, 0.67f, 0.8f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (auto& m : UIMeshes)
	{
		if (m->getCount() == 0) continue;
		if (!m->getReadyForDraw()) continue;
		m->Bind();
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

	UIMeshes.clear();
}