#include <glm/glm.hpp>


class IEntity {
public:
	glm::vec3 minAABB;
	glm::vec3 maxAABB;

	glm::vec3 velocity;
	glm::vec3 Pos;


};