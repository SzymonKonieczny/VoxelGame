#pragma once
#include <glm/glm.hpp>
#include "BlockInfo.h"
enum class ActionType {
	None, Break, Place, OpenConsole, PrintInfo
};
struct Action{
	//Action(ActionType type_ = ActionType::None, glm::vec3 Coordinates = {0,0,0}, 
	//	glm::vec3 Direction = { 0,0,0 }, float Range = 0.f)

	ActionType type;
	BlockName blockName;
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
	static Action PlaceAction(glm::vec3 Coordinates,  glm::vec3 Direction, float Range, BlockName blockName) {
		Action a;
		a.blockName = blockName;

		a.Coordinates = Coordinates;
		a.Direction = Direction;
		a.type = ActionType::Place;
		a.Range = Range;
		return a;
	}
	static Action OpenConsoleAction() {
		Action a;

		a.type = ActionType::OpenConsole;
		return a;
	}
	static Action PrintInfoAction() {
		Action a;

		a.type = ActionType::PrintInfo;
		return a;
	}
};