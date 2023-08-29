#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include "Chunk.h"
#include "../Renderer/Window.h"
#include "Renderer.h"
#include "Player.h"
#include "World.h"	
class Game
{
public:
	void Init();
	void Start();


	
	static int CHUNK_SIZE;
	static std::shared_ptr<Texture> BlockTextureAtlas;
private:
	World world;
	Player player;
	void Update(float dt);
};