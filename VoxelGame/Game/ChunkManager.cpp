#include "ChunkManager.h"
#include "Input.h"
void ChunkManager::GenerateChunksFromQueue(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (ChunksGenerationQueue.empty()) break;
		glm::ivec2 Pos = ChunksGenerationQueue.front();
		if (!ChunkMap.contains(Pos)) {
			ChunksGenerationQueue.pop();

			continue;
		}
		ChunkColumn& col = ChunkMap.at(Pos);
			ChunksGenerationQueue.pop();
		for (auto& chunk : col.m_Chunks) {
			Generator->generateTerrain(chunk);
			chunk.GenerateMesh();
		}
	}
}

void ChunkManager::UpdateLoadedChunkMap(glm::vec2 CenterPoint)
{
	int minX = CenterPoint.x - RenderDistance;
	int minZ = CenterPoint.y - RenderDistance;

	int maxX = CenterPoint.x + RenderDistance;
	int maxZ = CenterPoint.y + RenderDistance;


	for (int x = minX; x <= maxX; x++)
	{
		for (int z = minZ; z <= maxZ; z++)
		{
			if (ChunkMap.contains({ x,z }))
			{

			}
			else {
				ChunkMap.insert({ glm::ivec2(x, z), ChunkColumn(glm::ivec2(x, z)) });
				ChunksGenerationQueue.push(glm::ivec2(x, z));
			}
		}
	}

	for (auto it = ChunkMap.begin(); it!= ChunkMap.end();)
	{
		glm::ivec2 ColPos = it->first;
		if (ColPos.x > maxX || ColPos.x < minX ||
			ColPos.y >maxZ || ColPos.y < minZ) {
			it = ChunkMap.erase(it);
		}
		else it++;
	}

	GenerateChunksFromQueue(1);
if (Input::isPressed(GLFW_KEY_1))
	{
		std::cout << ChunkMap.size() << "ChunkMap size \n";
		for (auto it : ChunkMap)
		{
			std::cout << "ChunkPos : " << it.first.x << ' ' << it.first.y << '\n';
		}
	}
}
