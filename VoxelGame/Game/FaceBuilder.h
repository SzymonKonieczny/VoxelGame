#include "../Renderer/Mesh.h"
#include "BlockInfo.h"
enum class BlockFace {
	NORTH, //+z
	EAST, //+x
	SOUTH, //-z
	WEST, //-x
	UP,
	DOWN,
	X1,
	X2
};
class FaceBuilder
{
	struct chunkVertex {
		glm::vec3 Pos;
		glm::vec2 UV;
		float faceBightness; // default Top,Side,Down level of brightness
		float lightLevel; //light level at block
	};
	static void pushVertToMesh(Mesh& mesh, chunkVertex& vert)
	{
		float* ptr = (float*)&vert;
		
		for (int i = 0; i < sizeof(chunkVertex) / sizeof(float); i++)
		{
			mesh.Verticies.push_back(*ptr);
			ptr += 1;
		}
	}
public:
	static void BuildFace(Mesh& mesh, glm::vec3 pos, BlockFace Dir, glm::vec2 UV, int lightLevel) {
		
		//chunkVertex v{ glm::vec3(1.f,2.f,3.f), glm::vec2(1.f,2.f), glm::vec3(1.f,2.f,3.f) };
		//pushVertToMesh(mesh, v);
		chunkVertex v;
	
		//glm::vec3 Light = glm::vec3(0.05f, 0.05f, 0.05f);
		//Light += (float)lightLevel / 16.f; // divided by a little BIT more than 16

		float SideBrightness = 0.2f;
		float TopBrightness = 0.4f;
		float BottomBrightness = 0.1f;
		float light = (lightLevel / 16.f) * (1.f-TopBrightness);

		switch (Dir)
		{
		case BlockFace::NORTH: //+z
			 v={ pos + glm::vec3(0.f,0.f,1.f),UV+ glm::vec2(0.f,0.f),SideBrightness , light };
			 pushVertToMesh(mesh, v);
			 v = { pos + glm::vec3(1.f,0.f,1.f), UV + glm::vec2(0.2f,0.f),SideBrightness , light };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f),SideBrightness , light };
			 pushVertToMesh(mesh, v);
			 //----
			 v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(0.f,1.f,1.f), UV + glm::vec2(0.f,0.2f), SideBrightness , light };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(0.f,0.f,1.f), UV + glm::vec2(0.f,0.f), SideBrightness , light };
			 pushVertToMesh(mesh, v);




			break;
		case BlockFace::SOUTH :
			v = { pos + glm::vec3(0.f,0.f,0.f), UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.2f,0.f), SideBrightness ,light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,0.f), UV + glm::vec2(0.2f,0.2f), SideBrightness ,light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,0.f),UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			break;
		case BlockFace::EAST:
			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.f,0.f), SideBrightness ,light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,1.f,0.f),UV + glm::vec2(0.f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), SideBrightness ,  light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,0.f,1.f),UV + glm::vec2(0.2f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			break;
		case BlockFace::WEST:
			
			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(0.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,1.f),UV + glm::vec2(0.2f,0.f),SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			break;
		case BlockFace::UP:
			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.f), TopBrightness , light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,1.f,0.f),UV + glm::vec2(0.2f,0.f), TopBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), TopBrightness , light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), TopBrightness ,light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,1.f),UV + glm::vec2(0.f,0.2f), TopBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.f), TopBrightness , light };
			pushVertToMesh(mesh, v);
			break;
		case BlockFace::DOWN:
			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f),BottomBrightness , light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.2f,0.f), BottomBrightness ,light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,0.f,1.f),UV + glm::vec2(0.2f,0.2f), BottomBrightness , light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,0.f,1.f),UV + glm::vec2(0.2f,0.2f), BottomBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,1.f),UV + glm::vec2(0.f,0.2f), BottomBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), BottomBrightness , light };
			pushVertToMesh(mesh, v);
			break;


		case BlockFace::X1:
			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,1.f), UV + glm::vec2(0.2f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f), UV + glm::vec2(0.f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f), UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			break;
		case BlockFace::X2:
			v = { pos + glm::vec3(0.f,0.f,1.f),UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,0.f), UV + glm::vec2(0.2f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,0.f), UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,0.f), UV + glm::vec2(0.2f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,1.f), UV + glm::vec2(0.f,0.2f), SideBrightness , light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,1.f), UV + glm::vec2(0.f,0.f), SideBrightness , light };
			pushVertToMesh(mesh, v);
			break;
		default:

			break;
		}
			


		

		
	
	}
};