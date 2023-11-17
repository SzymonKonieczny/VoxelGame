
#pragma once
#include "ITerrainGenerator.h"
#include "Biomes/PlainsBiome.h"
#include "Biomes/DesertBiome.h"

enum class EarthBiomes {
	Plains = 1,
	Desert = (1 << 1)
};

class EarthyTerrainGenerator : public ITerrainGenerator {
	// Inherited via ITerrainGenerator
public:
	std::string BiomeDecisionTreeNode = "EABmZoZAEwAK1yM8DAABAAAAzczMPQkAAOF6lD8AuB6FPw==";
	std::string CaveCarvingTreeNode = "FwAAAEDAAABAQAAAgL8AAIA/EwCPwvU9GgABEQACAAAAAADgQBAAAACIQR8AFgABAAAACwADAAAAAgAAAAMAAAAEAAAAAAAAAD8BFAD//wAAAAAAAD8AAAAAPwAAAAA/AAAAAD8BFwAAAIC/AACAPz0KF0BSuB5AEwAAAKBABgAAj8J1PACamZk+AAAAAAABFwAAAIC/AACAPwAAAL8AAAA///8CAA==";


	std::vector<float> BiomeDecisionNoise= std::vector<float>(16 * 16);
	std::vector<float> HeightDecisionNoise = std::vector<float>(16 * 16);
	PlainsBiome Plains;
	DesertBiome Desert;
	EarthyTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef) {};
	virtual void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn) override;
	void generateCaves(std::shared_ptr<ChunkColumn>& chunkColumn);
	void FillHeightMapMultiBiome(std::shared_ptr<ChunkColumn>& chunkColumn);
	EarthBiomes DecideBiomeFromNoiseOutput(float noise);
	bool CheckForMultiBiomeChunk(ChunkColumn& chunkColumn);
	void generateLandMass(std::shared_ptr<ChunkColumn>& chunkColumn);
	void addIcing(std::shared_ptr<ChunkColumn>& chunkColumn);
};
