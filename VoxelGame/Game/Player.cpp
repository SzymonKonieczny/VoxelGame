#include "Player.h"
#include "Input.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <iostream>
Player::Player() : Pos(20,5,20), Rot(0,-0.6,-1), velocity(0,0,10)
{

}

void Player::Update(float dt)
{


	handleRotation();
	HandleMouseButtons();
	Move(dt);
	
	cam.SetPosition(Pos);
	cam.SetRotation(Rot);
	cam.UpdateMatricies(90.f,screenWidth/(float)screenHeight );
}

void Player::Move(float dt)
{
	if (Input::isPressed(GLFW_KEY_P))
	{
		std::cout << "Pos : " << Pos.x << ' ' << Pos.y << ' ' << Pos.z << "Rot :" << Rot.x << ' ' << Rot.y << ' ' << Rot.z << '\n';
	}

	if (Input::isPressed(GLFW_KEY_W))
	{
		velocity += speed * glm::normalize(glm::vec3(Rot.x,0, Rot.z)) *dt;
	}
	if (Input::isPressed(GLFW_KEY_A))
	{
		velocity += speed * dt * -glm::normalize(glm::cross(Rot, glm::vec3(0, 1, 0)));
	}
	if (Input::isPressed(GLFW_KEY_S))
	{
		velocity += speed * dt * -glm::normalize(glm::vec3(Rot.x, 0, Rot.z));
	}
	if (Input::isPressed(GLFW_KEY_D))
	{
		velocity += speed * dt * glm::normalize(glm::cross(Rot, glm::vec3(0,1,0)));
	}
	if (Input::isPressed(GLFW_KEY_SPACE))
	{
		velocity += speed * dt * glm::vec3(0, 1, 0);
	}
	if (Input::isPressed(GLFW_KEY_LEFT_SHIFT))
	{
		velocity += speed * dt * -glm::vec3(0, 1, 0);
	}
	if (Input::isPressed(GLFW_KEY_LEFT_CONTROL))
	{
		speed = 100.f;
	}
	else if (Input::isReleased(GLFW_KEY_LEFT_CONTROL))
	{
		speed = 10.f;
	}


	Pos += velocity;
	velocity.x *= drag * dt;
	velocity.z *= drag * dt;
	velocity.y *= drag * dt;
}

void Player::HandleMouseButtons()
{
	if (Input::mouseIsPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		actionQueue.push(ActionBuilder::BreakAction(cam.GetPosition(), cam.GetRotation(), 25));
	}
	else if (Input::mouseIsPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		actionQueue.push(ActionBuilder::PlaceAction(cam.GetPosition(), cam.GetRotation(), 25, BlockName::Wood));
	}
}

Action Player::GetAction()
{
	if (actionQueue.empty()) return Action(ActionType::None);
	Action ret = actionQueue.front();
	actionQueue.pop();
	return ret;
}

void Player::handleRotation()
{
	double mouseX, mouseY;
	Input::getMouseMove(&mouseX, &mouseY);
	float rotX = sensitivity * (float)(mouseY - (screenHeight / 2)) / screenHeight;
	float rotY = sensitivity * (float)(mouseX - (screenWidth / 2)) / screenWidth;

	glm::vec3 newOrientation = glm::rotate(Rot, glm::radians(-rotX), glm::normalize(glm::cross(Rot, glm::vec3(0, 1, 0))));

	if (abs(glm::angle(newOrientation, glm::vec3(0, 1, 0)) - glm::radians(90.0f)) <= glm::radians(90.0f))
	{
		Rot = newOrientation;
	}

	Rot = glm::rotate(Rot, glm::radians(-rotY), glm::vec3(0, 1, 0));
}
