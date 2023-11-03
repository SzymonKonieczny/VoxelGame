#include "World.h"
#include "Util.h"
#include <Windows.h>
BlockInfo World::GetBlockOnPosition(glm::vec3 Pos)
{
	return BlockTable[0];
}

void World::SetBlockOnPosition(glm::vec3 Pos, BlockName name)
{
	chunkManager->SetBlockAtPosition(Pos, name);
}

void World::TickWorld(double deltaTime)
{
	HandleActionQueue(1);
	player.Update(deltaTime);

	chunkManager->UpdateLoadedChunkMap({ player.getPositon().x / ChunkSize, player.getPositon().z / ChunkSize });

}

void World::HandleActionQueue(int amount)
{
	for (int i = 0; i < amount; i++)
	{

	
		Action action = player.GetAction();
		switch (action.type) {
			case ActionType::Break:
			{
				RayInfo info = Ray::Cast(action.Coordinates, action.Direction, *chunkManager, action.Range, RayType::BLOCK_RAY);
				if (!info.Miss)
				{

					SetBlockOnPosition(info.HitPos, BlockName::Air);

				}
			}
			break;
			case ActionType::Place:
			{
				RayInfo info = Ray::Cast(action.Coordinates, action.Direction, *chunkManager, action.Range, RayType::BLOCK_RAY);
				if (!info.Miss)
				{

					SetBlockOnPosition(info.HitFromPos, action.blockName);

				}
			}
			break;
			case ActionType::OpenConsole:
			{ //scope coz of variable creation
				std::string command;
				std::getline(std::cin, command);
				std::vector<float> args;
				CommandType Type = Util::ParseCommand(command, args);
					switch (Type)
					{
					case CommandType::Teleport:
						if (args.size() != 3)
						{
							std::cout << "Invalid argument count \n";
							continue;
						}
						player.getPositon().x = args[0];
						player.getPositon().y =  args[1];
						player.getPositon().z = args[2];
							break;

					case CommandType::GeneratorSwap:

						std::cout << "Causes crashes, command disabled \n";
						continue;

						if (args.size() != 1)
						{
							std::cout << "Invalid argument count \n";
							continue;
						}
						if (args[0] == 0) chunkManager->Generator.reset(new HeavenTerrainGenerator(chunkManager));
						if (args[0] == 1) chunkManager->Generator.reset(new EarthyTerrainGenerator(chunkManager));


						break;
					default:
						std::cout << "Invalid command \n";
						break;
					}
			}
			break;
			case ActionType::PrintInfo:
			{
				glm::vec3 Pos = player.getPositon();
				glm::vec3 Rot = player.getCamera().GetRotation();
				glm::vec3 ChunkPos = Util::WorldPosToChunkPos(Pos);
				std::cout << std::fixed << std::setprecision(2)
					<< "PlayerPos : " << Pos.x << '|' << Pos.y << '|' << Pos.z << '\n' <<
					   "PlayerRot :" << Rot.x << '|' << Rot.y << '|' << Rot.z << '\n' <<
						"ChunkPos :" << ChunkPos.x << '|' << ChunkPos.y << '|' << ChunkPos.z <<'\n';
			}
			break;
		}
	}
}
