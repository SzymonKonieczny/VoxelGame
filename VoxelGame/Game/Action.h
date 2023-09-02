#include <glm/glm.hpp>
enum class ActionType {
	Break, Place
};
struct Action{
	ActionType type;
	glm::vec3 Coordinates;
};