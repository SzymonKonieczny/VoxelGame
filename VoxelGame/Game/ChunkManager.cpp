#include "ChunkManager.h"
#include "Input.h"
void ChunkManager::GenerateChunksFromQueue(int amount )
{
	std::list<glm::ivec2> PosList;
	for (int i = 0; i<amount;i++)
	{
		if (ChunksGenerationQueue.empty()) break;
		PosList.push_back(ChunksGenerationQueue.front());
		ChunksGenerationQueue.pop();
	}
#if 0 //async chunk gen off
	std::thread ChunkGenerationThread(&ChunkManager::AsyncGenerateChunks, this, PosList, std::ref(isChunkGenerationThreadDone));
	ChunkGenerationThread.join();

#else
	AsyncGenerateChunks(PosList, std::ref(isChunkGenerationThreadDone));
#endif	
}

void ChunkManager::MeshChunksFromQueue(int amount)
{
	std::list<glm::ivec2> PosList;
	for (int i = 0; i < amount; i++)
	{
		if (ChunksMeshingQueue.empty()) break;
		PosList.push_back(ChunksMeshingQueue.front());
		ChunksMeshingQueue.pop();
	}

#if 0 //async chunk meshing off
	std::thread ChunkGenerationThread(&ChunkManager::AsyncGenerateChunks, this, PosList, std::ref(isChunkGenerationThreadDone));
	ChunkGenerationThread.join();

#else
	AsyncMeshChunks(PosList, std::ref(isChunkGenerationThreadDone));
#endif	
}

void ChunkManager::AsyncGenerateChunks(std::list<glm::ivec2> List, bool& isChunkGenerationThreadDoneFlag)
{
	isChunkGenerationThreadDoneFlag = false;
	for (auto& Pos : List)
	{
		if (ChunkMap.contains(Pos)) {
			ChunkColumn& col = ChunkMap.at(Pos);
			for (auto& chunk : col.m_Chunks) {
			
				Generator->generateTerrain(chunk);
				ChunksMeshingQueue.push(Pos);
				//chunk->GenerateMesh();
			}
		}
	}

	isChunkGenerationThreadDoneFlag = true;
}
void ChunkManager::AsyncMeshChunks(std::list<glm::ivec2> List, bool& isChunkMeshThreadDoneFlag)
{
	isChunkMeshThreadDoneFlag = false;
	for (auto& Pos : List)
	{
		if (ChunkMap.contains(Pos)) {
			ChunkColumn& col = ChunkMap.at(Pos);
			for (auto& chunk : col.m_Chunks) {

				chunk->GenerateMesh();
			}
		}
	}

	isChunkMeshThreadDoneFlag = true;
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
				ChunkMap.emplace( glm::ivec2(x, z), ChunkColumn(glm::ivec2(x, z)) );
				ChunksGenerationQueue.push(glm::ivec2(x, z));
			}
		}
	}
	//Remove outside (renderdistance + a little bit)
	minX  -= RenderDistance ;//*0.5;
	minZ  -= RenderDistance ;//* 0.5;
	maxX  += RenderDistance ;//* 0.5;
	maxZ  += RenderDistance ;//* 0.5;

	for (auto it = ChunkMap.begin(); it!= ChunkMap.end();)
	{
		glm::ivec2 ColPos = it->first;
		if (ColPos.x > maxX || ColPos.x < minX ||
			ColPos.y >maxZ || ColPos.y < minZ) {
			it = ChunkMap.erase(it);
		}
		else it++;
	}
//	GenerateChunksFromQueue(1);

	if (isChunkGenerationThreadDone) {
	
		isChunkGenerationThreadDone = false;
		GenerateChunksFromQueue(1);
	}
	MeshChunksFromQueue(1);
}

void ChunkManager::AddToMeshQueue(glm::ivec2 Coord)
{
	ChunksMeshingQueue.push(Coord);
}
