#include "ChunkManager.h"
#include "Input.h"
void ChunkManager::SetBlockAtPosition(glm::vec3 Position, BlockName name)
{
	glm::vec3 ChunkPos = Util::WorldPosToChunkPos(Position);
	if (ChunkPos.y < 0 || ChunkPos.y >= ChunksInColumn) { std::cout << "Trying to set block in a ChunkPos.y <0 OR ChunkPos.y >= ChunksInColumn@ ChunkManager::SetBlockAtPosition \n";  return; }

	glm::ivec2 ColumnPos = { ChunkPos.x,ChunkPos.z };
	if (ChunkMap.contains(ColumnPos))
	{
		glm::vec3 LocalPos = Util::WorldPosToLocalPos(Position);
		auto& column = ChunkMap.at(ColumnPos);
		auto& chunk = column->getChunk(ChunkPos.y);
		int index = Util::Vec3ToIndex(LocalPos);
		if (index < 0) return;
		chunk->blocks[index] = (unsigned int)name;
		chunk->setIsDirty(true);
		AddToMeshQueue(ChunkPos);
	}
	else
	{
		// ADD TO BLOCK QUEUE FOR NOT YET CREATED CHUNKS
	}
}
void ChunkManager::GenerateChunksFromQueue(int amount )
{
	std::list<glm::ivec2> PosList;
	for (int i = 0; i<amount;i++)
	{
		if (ChunksGenerationQueue.empty()) break;
		PosList.push_back(ChunksGenerationQueue.front());
		ChunksGenerationQueue.pop();
	}
#if 1 //async chunk gen off
	isChunkGenerationThreadDone = false;

	std::thread ChunkGenerationThread(&ChunkManager::AsyncGenerateChunks, this, PosList, std::ref(isChunkGenerationThreadDone));
	ChunkGenerationThread.join();

#else
	AsyncGenerateChunks(PosList, std::ref(isChunkGenerationThreadDone));
#endif	
}

void ChunkManager::MeshChunksFromQueue(int amount)
{
	if (!isChunkMeshThreadDone) return;
	std::list<glm::ivec3> PosList;
	for (int i = 0; i < amount; i++)
	{
		if (ChunksMeshingQueue.empty()) break;
		glm::ivec3 Pos =ChunksMeshingQueue.front();
		PosList.push_back(Pos);
		ChunksInMeshQueue.erase(Pos);
		ChunksMeshingQueue.pop();
	}

#if 1 //async chunk meshing off
	isChunkMeshThreadDone = false;
	std::thread ChunkMeshThread(&ChunkManager::AsyncMeshChunks, this, PosList, std::ref(isChunkMeshThreadDone));
	ChunkMeshThread.detach();

#else
	AsyncMeshChunks(PosList, std::ref(isChunkMeshThreadDone));
#endif	
}

void ChunkManager::AsyncGenerateChunks(std::list<glm::ivec2> List, bool& isChunkGenerationThreadDoneFlag)
{
	//isChunkGenerationThreadDoneFlag = false; Jest robione przed wywolaniem GenerateChunksFromQueue
	for (auto& Pos : List)
	{
		if (ChunkMap.contains(Pos)) {
			auto col = ChunkMap.at(Pos);
			Generator->generateTerrain(col); // potencjalnie generowanie chunka ktory w tym samym czasie bedzie usuniety
			for (auto& chunk : col->m_Chunks) {
			
				AddToMeshQueue(chunk->m_ChunkPos);
			}
		}
	}

	isChunkGenerationThreadDoneFlag = true;
}
void ChunkManager::AsyncMeshChunks(std::list<glm::ivec3> List, bool& isChunkMeshThreadDoneFlag)
{
	//isChunkMeshThreadDoneFlag = false; Jest robione przed wywolaniem MeshChunksFromQueue
	for (auto& Pos : List)
	{
		if (ChunkMap.contains(Pos)) {
			auto col = ChunkMap.at({ Pos.x,Pos.z });
			for (auto& chunk : col->m_Chunks) {

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
				ChunkMap.emplace( glm::ivec2(x, z), new ChunkColumn(glm::ivec2(x, z)));
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

	if (isChunkGenerationThreadDone) {
	
		GenerateChunksFromQueue(1);
	}
	if (isChunkMeshThreadDone) {


		MeshChunksFromQueue(5);

	}
}

void ChunkManager::AddToMeshQueue(glm::ivec3 Coord)
{
	if (ChunksInMeshQueue.contains(Coord))  return;
	ChunksMeshingQueue.push(Coord);
	ChunksInMeshQueue.emplace(Coord);
}
