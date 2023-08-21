#include "Chunk.h"

class Game
{
public:
	void Init();
	void Update();


	static int CHUNK_SIZE;
	static std::shared_ptr<Texture> BlockTextureAtlas;
};