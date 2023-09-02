#pragma once
#include "../Renderer/Camera.h"

class Player {

public:
	Player();
	void Update(float dt);
	void Move(float dt);
	Camera& getCamera() { return cam; }
	const glm::vec3& getPositon() { return Pos; };
private:
	void handleRotation();
	Camera cam;
	glm::vec3 Pos;
	glm::vec3 Rot;
	bool isOnGround=false;
	float speed = 0.1f;
	float sensitivity = 100.0f;
	float jumpForce = 0.2f;
	float BlocksCooldown = 0.1;
	float drag = 0.2f;
	glm::vec3 velocity;

};
