
#pragma once
#include "ITerrainGenerator.h"
#include "Biomes/PlainsBiome.h"
#include "Biomes/DesertBiome.h"
#include "Biomes/ForestBiome.h"
#include "Biomes/FallForestBiome.h"
enum class EarthBiomes {
	Plains,
	Desert,
	Forest,
	FallForest
};

class EarthyTerrainGenerator : public ITerrainGenerator {
	// Inherited via ITerrainGenerator
public:
	
	//std::string BiomeDecisionTreeNode = "EABmZoZAEwDhepQ+DAABAAAAzczMPQkAAOF6lD8AuB6FPw==";		// Smaller biomes
	std::string BiomeDecisionTreeNode = "EABmZoZAEwCPwvU8DAABAAAAzczMPQkAAOF6lD8AuB6FPw==";	// Larget Biomes
	std::string CaveCarvingTreeNode = "FwAAAEDAAABAQAAAgL8AAIA/EwCPwvU9GgABEQACAAAAAADgQBAAAACIQR8AFgABAAAACwADAAAAAgAAAAMAAAAEAAAAAAAAAD8BFAD//wAAAAAAAD8AAAAAPwAAAAA/AAAAAD8BFwAAAIC/AACAPz0KF0BSuB5AEwAAAKBABgAAj8J1PACamZk+AAAAAAABFwAAAIC/AACAPwAAAL8AAAA///8CAA==";


	std::vector<float> BiomeDecisionNoise= std::vector<float>(16 * 16);
	std::vector<float> HeightDecisionNoise = std::vector<float>(16 * 16);
	std::vector<std::unique_ptr<IBiome>> Biomes;

	EarthyTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef);

	virtual void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn) override;
	void generateCaves(std::shared_ptr<ChunkColumn>& chunkColumn);
	void FillHeightMapMultiBiome(std::shared_ptr<ChunkColumn>& chunkColumn);
	float getHeightAtBlock(glm::vec2 WorldPos);
	EarthBiomes DecideBiomeFromNoiseOutput(float noise);
	bool CheckForMultiBiomeChunk(ChunkColumn& chunkColumn);
	void generateLandMass(std::shared_ptr<ChunkColumn>& chunkColumn);
	void addIcing(std::shared_ptr<ChunkColumn>& chunkColumn);
	float getMapHeightAtPosition(glm::vec2 worldPos);
	
};
