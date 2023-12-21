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
		glm::vec3 Col;

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
	
		glm::vec3 Light = glm::vec3(0.15f, 0.15f, 0.15f);
		Light += (float)lightLevel / 18.f; // divided by a little BIT more than 16
		switch (Dir)
		{
		case BlockFace::NORTH: //+z
			 v={ pos + glm::vec3(0.f,0.f,1.f),UV+ glm::vec2(0.f,0.f),	glm::vec3(0.25f,0.25f,0.25f) + Light };
			 pushVertToMesh(mesh, v);
			 v = { pos + glm::vec3(1.f,0.f,1.f), UV + glm::vec2(0.2f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			 pushVertToMesh(mesh, v);
			 //----
			 v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(0.f,1.f,1.f), UV + glm::vec2(0.f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(0.f,0.f,1.f), UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			 pushVertToMesh(mesh, v);




			break;
		case BlockFace::SOUTH :
			v = { pos + glm::vec3(0.f,0.f,0.f), UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.2f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,0.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,0.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			break;
		case BlockFace::EAST:
			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,1.f,0.f),UV + glm::vec2(0.f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,0.f,1.f),UV + glm::vec2(0.2f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			break;
		case BlockFace::WEST:
			
			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f),glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(0.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,1.f),UV + glm::vec2(0.2f,0.f),glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			break;
		case BlockFace::UP:
			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.3f,0.3f,0.3f) + Light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,1.f,0.f),UV + glm::vec2(0.2f,0.f), glm::vec3(0.3f,0.3f,0.3f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.3f,0.3f,0.3f) + Light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.3f,0.3f,0.3f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,1.f),UV + glm::vec2(0.f,0.2f), glm::vec3(0.3f,0.3f,0.3f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.3f,0.3f,0.3f) + Light };
			pushVertToMesh(mesh, v);
			break;
		case BlockFace::DOWN:
			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.5f,0.5f,0.5f) };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,0.f),UV + glm::vec2(0.2f,0.f), glm::vec3(0.5f,0.5f,0.5f) };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,0.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.5f,0.5f,0.5f) };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,0.f,1.f),UV + glm::vec2(0.2f,0.2f), glm::vec3(0.5f,0.5f,0.5f) };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,1.f),UV + glm::vec2(0.f,0.2f), glm::vec3(0.5f,0.5f,0.5f) };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.5f,0.5f,0.5f) };
			pushVertToMesh(mesh, v);
			break;


		case BlockFace::X1:
			v = { pos + glm::vec3(0.f,0.f,0.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,1.f), UV + glm::vec2(0.2f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,1.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,0.f), UV + glm::vec2(0.f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,0.f), UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			break;
		case BlockFace::X2:
			v = { pos + glm::vec3(0.f,0.f,1.f),UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			v = { pos + glm::vec3(1.f,0.f,0.f), UV + glm::vec2(0.2f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(1.f,1.f,0.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			//----
			v = { pos + glm::vec3(1.f,1.f,0.f), UV + glm::vec2(0.2f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,1.f,1.f), UV + glm::vec2(0.f,0.2f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);

			v = { pos + glm::vec3(0.f,0.f,1.f), UV + glm::vec2(0.f,0.f), glm::vec3(0.25f,0.25f,0.25f) + Light };
			pushVertToMesh(mesh, v);
			break;
		default:

			break;
		}
			


		

		
	
	}
};