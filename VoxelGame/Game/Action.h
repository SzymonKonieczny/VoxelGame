#pragma once
#include <glm/glm.hpp>
enum class ActionType {
	None, Break, Place
};
struct Action{
	//Action(ActionType type_ = ActionType::None, glm::vec3 Coordinates = {0,0,0}, 
	//	glm::vec3 Direction = { 0,0,0 }, float Range = 0.f)

	ActionType type;
	glm::vec3 Coordinates;
	glm::vec3 Direction;
	float Range;


};
class ActionBuilder
{
public:
	static Action BreakAction(glm::vec3 Coordinates, glm::vec3 Direction, float Range) {
		Action a;
		a.Coordinates = Coordinates;
		a.Direction = Direction;
		a.type = ActionType::Break;
		a.Range = Range;
		return a;
	}

};