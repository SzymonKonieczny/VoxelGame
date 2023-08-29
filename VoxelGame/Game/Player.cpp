#include "Player.h"
#include "Input.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
Player::Player() : Pos(0,0,0), Rot(0,0,0)
{
}

void Player::Update(float dt)
{


	handleRotation();
	Move();
	cam.SetPosition(Pos);
	cam.SetRotation(Rot);
	cam.UpdateMatricies();
}

void Player::Move()
{
}

void Player::handleRotation()
{
	double mouseX, mouseY;
	Input::getMouseMove(&mouseX, &mouseY);
	float rotX = sensitivity * (float)(mouseY - (screenHeight / 2)) / screenHeight;
	float rotY = sensitivity * (float)(mouseX - (screenWidth / 2)) / screenWidth;

	glm::vec3 newOrientation = glm::rotate(Rot, glm::radians(-rotX), glm::normalize(glm::cross(Rot, glm::vec3(0, 1, 0))));

	if (abs(glm::angle(newOrientation, glm::vec3(0, 1, 0)) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Rot = newOrientation;
	}

	Rot = glm::rotate(Rot, glm::radians(-rotY), glm::vec3(0, 1, 0));

}
