#include "ChunkManager.h"
#include "Input.h"
#include <Windows.h>
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
		chunk->setBlock(name, index);;
		chunk->setIsDirty(true);

		AddToMeshQueue(ChunkPos);
	}
	else
	{
		// ADD TO BLOCK QUEUE FOR NOT YET CREATED CHUNKS
	}
}
BlockName ChunkManager::GetBlockAtPosition(glm::vec3 Position)
{
	BlockName ret = BlockName::Air;
	glm::vec3 ChunkPos = Util::WorldPosToChunkPos(Position);
	if (ChunkPos.y < 0 || ChunkPos.y >= ChunksInColumn) {
		//std::cout << "Trying to set block in a ChunkPos.y <0 OR ChunkPos.y >= ChunksInColumn@ ChunkManager::GetBlockAtPosition \n";
		return ret; 
	}

	glm::ivec2 ColumnPos = { ChunkPos.x,ChunkPos.z };
	if (ChunkMap.contains(ColumnPos))
	{
		glm::vec3 LocalPos = Util::WorldPosToLocalPos(Position);
		auto& column = ChunkMap.at(ColumnPos);
		auto& chunk = column->getChunk(ChunkPos.y);
		int index = Util::Vec3ToIndex(LocalPos);
		if (index < 0) {
			std::cout << "Reading blocks[<0] @ ChunkManager::GetBlockAtPosition \n";
			return ret;
		}

		ret = (BlockName)chunk->getBlock(index);

	}
	return ret;
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
	ChunkGenerationThread.detach();

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
		glm::ivec3 Pos = GetFromMeshQueue();
		//if (ChunkMap.at({ Pos.x,Pos.z})->m_Chunks[Pos.y]->isDirty() //Checking if the chunk is dirty
		//	&& ChunksInMeshQueue.contains(Pos))
		{
			PosList.push_back(Pos);
			ChunksInMeshQueue.erase(Pos);
		}


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
			
			Generator->generateTerrain(col); 
			AddColumnToMeshQueue(Pos);

			AddColumnToMeshQueue(glm::ivec2(Pos.x, Pos.y-1));
			//AddColumnToMeshQueue(glm::ivec2(Pos.x+1, Pos.y));
			//AddColumnToMeshQueue(glm::ivec2(Pos.x, Pos.y-1));
			//AddColumnToMeshQueue(glm::ivec2(Pos.x, Pos.y+1));


		}
	}

	isChunkGenerationThreadDoneFlag = true;
}
void ChunkManager::AsyncMeshChunks(std::list<glm::ivec3> List, bool& isChunkMeshThreadDoneFlag)
{

	//isChunkMeshThreadDoneFlag = false; Jest robione przed wywolaniem MeshChunksFromQueue
	for (auto& Pos : List)
	{
		if (ChunkMap.contains({ Pos.x,Pos.z })) {
			auto col = ChunkMap.at({ Pos.x,Pos.z });
			if (Pos.y < col->m_Chunks.size())
			{
				col->m_Chunks[Pos.y]->GenerateLightmap();
				col->m_Chunks[Pos.y]->GenerateMesh();
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
				ChunkMap.emplace( glm::ivec2(x, z), new ChunkColumn(glm::ivec2(x, z), selfSmartPointer));
				ChunksGenerationQueue.push(glm::ivec2(x, z));
			}
		}
	}
	//Remove outside (renderdistance + a little bit)
	minX  -= RenderDistance  *0.5;
	minZ  -= RenderDistance  * 0.5;
	maxX  += RenderDistance  * 0.5;
	maxZ  += RenderDistance  * 0.5;
							 
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
	
		GenerateChunksFromQueue(RenderDistance);
	}
	if (isChunkMeshThreadDone) {


		MeshChunksFromQueue(ChunksInColumn+5);

	}
}

void ChunkManager::AddToMeshQueue(glm::ivec3 Coord)
{
	MeshingQueueMutex.lock();
	if (ChunksInMeshQueue.contains(Coord))
	{
		MeshingQueueMutex.unlock();
		return;

	}
	ChunksMeshingQueue.push(Coord);
	ChunksInMeshQueue.emplace(Coord);
	MeshingQueueMutex.unlock();

}
void ChunkManager::AddColumnToMeshQueue(glm::ivec2 Pos)
{
	if (ChunkMap.contains(Pos))
	{
		auto col = ChunkMap.at(Pos);
		if (col->nrOfRemeshes > 2)
		{
			return;
		}
		col->nrOfRemeshes += 1;
			for (auto& chunk : col->m_Chunks)
				AddToMeshQueue(chunk->m_ChunkPos);

	}
}
void ChunkManager::PropagateLightToChunks(glm::vec3 Pos, int strength)
{

		if (strength <= 0) return;
		glm::vec3 ChunkPos = Util::WorldPosToChunkPos(Pos);

		if (ChunkMap.contains(ChunkPos))
		{
			glm::ivec2 ColumnPos = { ChunkPos.x,ChunkPos.z };
			glm::vec3 LocPos = Util::WorldPosToLocalPos(Pos);
			auto& chunk = ChunkMap.at(ColumnPos)->m_Chunks[ChunkPos.y];
			
			if (BlockTable[chunk->getBlock(LocPos)].isSold) return;
			if (chunk->getLightLevel(LocPos) >= strength) return;


			PropagateLightToChunks({ Pos.x + 1,Pos.y,Pos.z }, strength - 1);
			PropagateLightToChunks({ Pos.x - 1,Pos.y,Pos.z }, strength - 1);
			PropagateLightToChunks({ Pos.x,Pos.y + 1,Pos.z }, strength - 1);
			PropagateLightToChunks({ Pos.x,Pos.y - 1,Pos.z }, strength - 1);
			PropagateLightToChunks({ Pos.x,Pos.y,Pos.z + 1 }, strength - 1);
			PropagateLightToChunks({ Pos.x,Pos.y,Pos.z - 1 }, strength - 1);


			chunk->setLightLevel(LocPos, strength);


		}



}
glm::ivec3 ChunkManager::GetFromMeshQueue()
{
	MeshingQueueMutex.lock();

	glm::ivec3 ret =ChunksMeshingQueue.front();
	ChunksMeshingQueue.pop();
	MeshingQueueMutex.unlock();
	return ret;

}