#pragma once
#include "ChunkManager.h"
#include "Action.h"
#include "BlockInfo.h"
#include "Player.h"
#include "Ray.h"
#include <string>
#include <iomanip>
struct Comma final : std::numpunct<char>
{
	char do_decimal_point() const override { return ','; }
};
class World {
public:
	std::shared_ptr<ChunkManager> chunkManager;
	World() {
		chunkManager.reset(new ChunkManager());
		FrameTimes.reserve(2000000);
	}
	~World()
	{
		std::ofstream outputFile("FrameTimes.csv", std::ios::binary | std::ios::trunc);

		outputFile << "FrameTime;FrameNr;ElapsedTime\n";
		outputFile.imbue(std::locale(std::locale::classic(), new Comma));
		float ElapsedTime = 0;
		for (size_t i = 1; i < FrameTimes.size(); i++)
		{
			outputFile << FrameTimes[i] << ';' << i << ';' << ElapsedTime << '\n';
			ElapsedTime += FrameTimes[i];
			if (ElapsedTime >= 60) break;
		}	
		outputFile.close();
	}
	BlockInfo GetBlockOnPosition(glm::vec3 Pos);
	void SetBlockOnPosition(glm::vec3 Pos, BlockName name);
	void TickWorld(double deltaTime);
	void HandleActionQueue(int amount);
	Player player; 
	std::vector<float> FrameTimes;
	bool countFrames = false;

};
