
#include "Game.h"
#include "Input.h"
#include <glm/gtx/rotate_vector.hpp>
#include "UI/UIHUD.h"
//int Game::CHUNK_SIZE = 16;
std::shared_ptr<Texture> Game::BlockTextureAtlas;
std::shared_ptr<Texture> Game::ItemTextureAtlas;

void Game::Init()
{
	Renderer::Init();
	Input::windowptr = Renderer::window.GetHandle();

	BlockTextureAtlas.reset(new Texture("Game/Textures/Atlas.png"));
	Chunk::ChunkSolidShader.reset(new Shader("Game/Shaders/ChunkShader.vert", "Game/Shaders/ChunkShader.frag"));

	ItemTextureAtlas.reset(new Texture("Game/Textures/ItemAtlas.png"));
	UIElement::UIShader.reset(new Shader("Game/Shaders/UIShader.vert", "Game/Shaders/UIShader.frag"));


}

void Game::Start()
{
	
	
	FillBlockTable();
	FillItemTable();
	world.player.GenerateUIs();


	double previousTime = glfwGetTime();
	double deltaTime;
	double currentTime = 0;
	glfwSwapInterval(0);
	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		{
			std::string FPS = std::to_string((1.0 / deltaTime));
			std::string newTitle = "Voxelini Kowalini  " + FPS + " FPS";
			glfwSetWindowTitle(Renderer::window.GetHandle(), newTitle.c_str());
		}

		Renderer::BeginScene(world.player.getCamera());
		Update(deltaTime);

		RenderWorld(world);
		world.player.DrawUI();
		Renderer::EndScene();
		Renderer::window.SwapBuffers();

		Renderer::window.PullEvents();
	}

}

void Game::RenderWorld(World& world)
{
	for (auto& chunkCol : world.chunkManager->getChunks())
	{
		if (isChunkColumnInFrustum(chunkCol.second))
		{
			for (auto& chunk : chunkCol.second->m_Chunks) {
				if (chunk->isGPU_BufferOutdated() /* && chunk->isMeshed() Not needed,
												  we set outdated at the end of the meshing process anyways*/)
				{
					chunk->getMesh().UpdateObjectsOnGPU();
					chunk->setIsGPU_BufferOutdated(false);
				}
				Renderer::SubmitChunk(chunk->getMesh());
			}
		}

	}
}

float area(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f);
}

bool Game::isChunkColumnInFrustum(std::shared_ptr<ChunkColumn> col)
{
	glm::vec2 playerPos(world.player.getPositon().x/ChunkSize, world.player.getPositon().z/ ChunkSize);//first check if in render distance, later actual frustum
	glm::vec2 colPos(col->m_Position.x, col->m_Position.y);
	if (!(RenderDistance > glm::distance(colPos, playerPos)))return false; //fcked up logic but it works xd
	
	
	glm::vec3 Cam, Left, Right;
	float FarPlane = 1000; //world.player.getCamera().GetFarPlane();
	//(world.player.getPositon().x, world.player.getPositon().z);
	float Opposite;//Opposite side to the angle on the triangle
	Opposite = glm::tan(world.player.FOV / 2) * FarPlane; //glm::sin(world.player.FOV / 2) / (FarPlane / glm::cos(world.player.FOV / 2));
	Opposite = 2000; //temp
	Cam = glm::vec3(0,0,-50);
	Left = Cam + glm::vec3(-Opposite,0, FarPlane );
	Right = Cam + glm::vec3(Opposite,0, FarPlane );
	glm::mat4 Transformation(1);
	Transformation = glm::translate(Transformation, world.player.getPositon());
	float angleY = atan2(-world.player.getCamera().GetViewMatrix()[0][2], world.player.getCamera().GetViewMatrix()[2][2]);

	Transformation = glm::rotate(Transformation, angleY - glm::radians(180.f), glm::vec3(0, -1, 0));
	Cam = glm::vec3(Transformation* glm::vec4(Cam, 1.0f) );
	Left = glm::vec3(Transformation* glm::vec4(Left, 1.0f) );
	Right = glm::vec3(Transformation* glm::vec4(Right, 1.0f) );

	glm::vec3 MeshPos(col->m_Position.x * ChunkSize, 0, col->m_Position.y * ChunkSize);

	float FrustumArea = area(Cam.x, Cam.z, Left.x, Left.z, Right.x, Right.z);

	float Area = 0;
	Area += area(MeshPos.x, MeshPos.z, Left.x, Left.z, Right.x, Right.z);
	Area += area(Cam.x, Cam.z, MeshPos.x, MeshPos.z, Right.x, Right.z);
	Area += area(Cam.x, Cam.z, Left.x, Left.z, MeshPos.x, MeshPos.z);

	if (abs(FrustumArea - Area) < 10.f) return true;

	auto dist = glm::distance(Left, Right);
	return false;
}

void Game::FillBlockTable()
{

	BlockTable.push_back(BlockInfo({ 0.8f,0.f },BlockModelType::Cube, true, false,false)); //AIR
	BlockTable.push_back(BlockInfo({ 0.f,0.f }, { 0.2f,0.6f }, { 0.6f,0.f }, BlockModelType::Cube, false, true)); //Grass
	BlockTable.push_back(BlockInfo({ 0.2f,0.f }, BlockModelType::Cube, false, true,true)); //Ore
	BlockTable.push_back(BlockInfo({ 0.4f,0.f }, BlockModelType::Cube, false, true, true)); //Stone
	BlockTable.push_back(BlockInfo({ 0.6f,0.f }, BlockModelType::Cube, false, true, true)); //Dirt
	BlockTable.push_back(BlockInfo({ 0.8f,0.f }, BlockModelType::Cube, false, false, true)); //Wood
	BlockTable.push_back(BlockInfo({ 0.8f,0.4f }, BlockModelType::X, false, false, true, 10)); //Rose
	BlockTable.push_back(BlockInfo({ 0.2f,0.2f }, BlockModelType::Cube, false, true, true)); //Sand
	BlockTable.push_back(BlockInfo({ 0.0f,0.2f }, BlockModelType::Cube, false, false, true)); //Leaves
	BlockTable.push_back(BlockInfo({ 0.6f,0.6f }, { 0.4f,0.6f }, { 0.6f,0.f }, BlockModelType::Cube, false, true)); //RedGraass
	BlockTable.push_back(BlockInfo({ 0.8f,0.6f }, BlockModelType::Cube, false, false, true)); //RedLeaves
	BlockTable.push_back(BlockInfo({ 0.8f,0.f }, BlockModelType::Cube, false, false, true,5)); //GlowWood




	
}

void Game::FillItemTable()
{
	ItemTable.push_back(ItemInfo(glm::vec2(0, 0)));//AIR
	ItemTable.push_back(ItemInfo(glm::vec2(0.1f, 0), (int)BlockName::Dirt));//TEST
	ItemTable.push_back(ItemInfo(glm::vec2(0.2f, 0), (int)BlockName::Grass));//Grass
	ItemTable.push_back(ItemInfo(glm::vec2(0.3f, 0), (int)BlockName::Ore));//Ore
	ItemTable.push_back(ItemInfo(glm::vec2(0.4f, 0), (int)BlockName::Dirt));//Dirt
	ItemTable.push_back(ItemInfo(glm::vec2(0.5f, 0),(int)BlockName::Wood));//Wood


}

void Game::Update(double dt)
{
	world.TickWorld(dt);
}
