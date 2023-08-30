#include "Renderer.h"
#include "Input.h"
Window Renderer::window; //constructor static call
glm::mat4 Renderer::ViewProjectionMatrix;
std::list<Mesh*> Renderer::Meshes;
std::unique_ptr<Framebuffer> frame;//(FramebufferOptions(screenWidth,screenHeight )); //Width, Height
std::unique_ptr < Mesh> ScreenQuad;
void Renderer::Init()
{
	window.Init();
	
	glfwSetWindowSizeCallback(window.GetHandle(), OnWindowResize);
	RendererCommand::SetViewport(0, 0, screenWidth,screenHeight);

	frame.reset(new Framebuffer(FramebufferOptions(screenWidth, screenHeight)));
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
	ScreenQuad->updateUniform("screenTexture", 0);


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


}

void Renderer::EndScene()
{
	frame->Bind();
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
	glClear(GL_COLOR_BUFFER_BIT);

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
