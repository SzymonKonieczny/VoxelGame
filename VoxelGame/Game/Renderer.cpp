#include "Renderer.h"
#include "Input.h"
Window Renderer::window; //constructor static call
glm::mat4 Renderer::ViewProjectionMatrix;
std::list<Mesh> Renderer::Meshes;
/*Framebuffer Renderer::frame({800, 800});
Mesh ScreenQuad;

std::string vertSrc = R"(
#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoords;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0); 
    texCoords = inTexCoords;
}  )";
std::string fragSrc = R"(
#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;


void main()
{
    vec3 color = vec3(0.0f);
    FragColor = vec4(color, 1.0f);
})";
BufferLayout ScreenShaderLayout = {
	{ShaderDataType::Float2, "inPos"},
	{ShaderDataType::Float2, "inTexCoords"}
};

Shader ScreenShader(vertSrc, fragSrc);
*/

void Renderer::Init()
{
	window.Init();
	
	glfwSetWindowSizeCallback(window.GetHandle(), OnWindowResize);
	RendererCommand::SetViewport(0, 0, screenWidth,screenHeight);

	/*ScreenQuad.GetVertexArray().SetVertexBuffer(new VertexBuffer());
	ScreenQuad.Verticies = {
		// Coords    // texCoords
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,
	
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};
	ScreenQuad.GetVertexArray().SetLayout(ScreenShaderLayout);
	ScreenQuad.UpdateGLObjs();
	
	ScreenShader.Bind();
	GLuint textureSamplerLoc = ScreenShader.GetUniformLocation("screenTexture");
	glUniform1i(textureSamplerLoc, 0);*/

}

void Renderer::Shutdown()
{
	window.Shutdown();
}

void Renderer::OnWindowResize(GLFWwindow* window, int width, int height)
{
	
}

void Renderer::BeginScene(Camera& camera) // argument : vec<ligtsources>
{
	ViewProjectionMatrix =  camera.GetProjectionMatrix()* camera.GetViewMatrix();


}

void Renderer::EndScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//frame.Bind();
	for (auto& m : Meshes)
	{
		m.Bind();
		if (m.hasUniform("viewProjMatrix")) m.updateUniform("viewProjMatrix", ViewProjectionMatrix);
		m.PreDraw();
		switch (m.getType())
		{
		case MeshType::Indexed:
			RendererCommand::DrawIndexed(m);
			break;
		case MeshType::Unindexed:
			
			RendererCommand::DrawNotIndexed(m);
			break;
		}
	}
	
	Meshes.clear();


}

void Renderer::Submit(Mesh& m)
{
	Meshes.push_back(m);
}
