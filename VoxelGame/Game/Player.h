#pragma once
#include "../Renderer/Camera.h"
#include "Action.h"
#include "PointCollider.h"
#include "BlockInfo.h"
#include "PointCollider.h"
#include <queue>
class Player {

public:
	Player();
	void Update(float dt);
	void Move(float dt);
	void HandleMouseButtons();
	Camera& getCamera() { return cam; }
	const glm::vec3& getPositon() { return Pos; };
	Action GetAction();
private:
	
	void handleCollisions();
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
	bool noClip = true;
	glm::vec3 velocity;
	std::queue<Action> actionQueue;


};
