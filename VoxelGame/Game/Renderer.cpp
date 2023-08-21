#include "Renderer.h"
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
void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}
void Renderer::Init()
{
	window.Init();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glfwSetWindowSizeCallback(window.GetHandle(), OnWindowResize);
	RendererCommand::SetViewport(0, 0, 800, 800);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);


	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

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
	ViewProjectionMatrix = camera.GetViewMatrix() * camera.GetProjectionMatrix();


}

void Renderer::EndScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//frame.Bind();



	for (auto& m : Meshes)
	{
		switch (m.getType())
		{
		case MeshType::Indexed:
			RendererCommand::DrawIndexed(m);
			break;
		case MeshType::Unindexed:
			RendererCommand::DrawNotIndexed(m, ViewProjectionMatrix);
			break;
		}
	}
	
	Meshes.clear();


}

void Renderer::Submit(Mesh& m)
{
	Meshes.push_back(m);
}
