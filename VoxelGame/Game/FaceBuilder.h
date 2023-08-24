#include "../Renderer/Mesh.h"
enum class BlockFace {
	NORTH, //+z
	EAST, //+x
	SOUTH, //-z
	WEST //-x
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
	static void BuildFace(Mesh& mesh, glm::vec3 pos, BlockFace Dir) {
		
		//chunkVertex v{ glm::vec3(1.f,2.f,3.f), glm::vec2(1.f,2.f), glm::vec3(1.f,2.f,3.f) };
		//pushVertToMesh(mesh, v);
		chunkVertex v;
		switch (Dir)
		{
		case BlockFace::NORTH: //+z
			 v={ pos + glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,0.f), glm::vec3(1.f,1.f,1.f) };
			 pushVertToMesh(mesh, v);
			 v = { pos + glm::vec3(1.f,0.f,1.f), glm::vec2(0.2f,0.f), glm::vec3(1.f,1.f,1.f) };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(1.f,1.f,1.f), glm::vec2(0.2f,0.2f), glm::vec3(1.f,1.f,1.f) };
			 pushVertToMesh(mesh, v);
			 //----
			 v = { pos + glm::vec3(1.f,1.f,1.f), glm::vec2(0.2f,0.2f), glm::vec3(1.f,1.f,1.f) };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(0.f,1.f,1.f), glm::vec2(0.f,0.2f), glm::vec3(1.f,1.f,1.f) };
			 pushVertToMesh(mesh, v);

			 v = { pos + glm::vec3(0.f,0.f,1.f), glm::vec2(0.f,0.f), glm::vec3(1.f,1.f,1.f) };
			 pushVertToMesh(mesh, v);




			break;
		default:

			break;
		}
	}
};