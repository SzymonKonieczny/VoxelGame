#pragma once
#include "ChunkColumn.h"
#include <fstream>
#include <sstream>
#include <exception>
class FileLoader {
public:

	static void LoadWorldFile(std::unordered_map<glm::ivec2, std::vector<unsigned int>>& CompressedLoadedSaveMap, std::string FileName) {
        std::ifstream inputFile(FileName);

        if (!inputFile.is_open()) {
            std::cerr << "Unable to open the file: " << FileName << std::endl;
            return; 
        }

        std::string line;
            try {

                while (std::getline(inputFile, line, char(255))) { //what if theres 255 of some block in a row and it appears in the datablock
                    std::stringstream ss;
                    glm::ivec2 Pos;
                    ss << line;
                    ss >> Pos.x;
                    ss >> Pos.y;
                    std::vector<char> data;
                    data.reserve(ChunkSize * ChunkSize * ChunkSize * 2); //worst case secenario where every block is diffrent.
                    char temp;
                    while (ss >> temp)  //shove bytes into the data vector
                    {
                        data.push_back(temp);
                    }

                    if ((data.size() / sizeof(float)) / 2 % 2 != 0)
                           throw std::runtime_error("Invalid size of the datablock");

                    CompressedLoadedSaveMap.emplace(Pos, std::vector<unsigned int>()); //add the new entry to the map of mapped chunk columns to data
                    auto& BlockData = CompressedLoadedSaveMap[Pos];           //now use it to fill it with data
                    BlockData.reserve(data.size() / sizeof(float));
                    for (int i = 0; i < data.size(); i+= sizeof(float))
                    {
                        BlockData.push_back(*(unsigned int*)&data[i]);
                    }

                    //here BlockData contains data ints that can be put in pairs : (Int,Int)(Int,Int)
                }

            }
            catch( std::exception& e){
                std::cerr << "Loading the world failed, generating a new world" << std::endl;
                std::cout << "Error was : " << e.what() << std::endl;
            }

        inputFile.close();

	}
    static void SaveWorldFile(std::unordered_map<glm::ivec2, std::shared_ptr<ChunkColumn>>& ChunkMap, std::string FileName)
    {
        std::ofstream outputFile(FileName, std::ios::binary | std::ios::trunc);

        // Check if the file is open
        if (!outputFile.is_open()) {
            std::cerr << "Unable to open the file for writing: " << FileName << std::endl;
            return; // Exit the function if the file cannot be opened
        }

        for (auto& ChunkCol : ChunkMap)
        {
            auto Pos = ChunkCol.first;
            outputFile << Pos.x << ' ' << Pos.y << ' ';

            for (int i = 0; i< ChunkCol.second->m_Chunks.size(); i++)
            {
                ChunkCol.second->m_Chunks[i]->blockMutex.lock();
                auto& blockVec = ChunkCol.second->m_Chunks[i]->getBlocksVector();
                std::vector<unsigned int> compressedBlockVector = compressBlocks(blockVec);

                outputFile.write((const char*)compressedBlockVector.data(),  // char = (char)10 daje nam newline, wiec blocki ID 10 psuja outfile
                    compressedBlockVector.size() * sizeof(unsigned int));

            }
            outputFile << '\n';

        }


        // Close the file
        outputFile.close();

    }

    static std::vector<unsigned int> compressBlocks(const std::vector<unsigned int>& blocks) {
        std::vector<unsigned int> compressedData;

        // Check if the input vector is empty
        if (blocks.empty()) {
            std::cerr << "Input vector is empty." << std::endl;
            return compressedData;
        }

        // Initialize variables for tracking the streak
        int currentStreakValue = blocks[0];
        int currentStreakLength = 1;

        // Iterate through the blocks
        for (size_t i = 1; i < blocks.size(); ++i) {
            if (blocks[i] == currentStreakValue) {
                // Increment the streak length
                ++currentStreakLength;
            }
            else {
                // Store the streak value and length
                compressedData.push_back(currentStreakValue);
                compressedData.push_back(currentStreakLength);

                // Start a new streak
                currentStreakValue = blocks[i];
                currentStreakLength = 1;
            }
        }

        // Process the last streak
        compressedData.push_back(currentStreakValue);
        compressedData.push_back(currentStreakLength);

        return compressedData;
    }
};
