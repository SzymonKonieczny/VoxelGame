#pragma once
#include "../Renderer/Camera.h"
#include "Action.h"
#include "PointCollider.h"
#include "BlockInfo.h"
#include "PointCollider.h"
#include <queue>
#include "UI/UIHUD.h"
class Player {

public:
	Player();

	void Update(float dt);
	void Move(float dt);
	void HandleMouseButtons();
	void GenerateUIs();
	Camera& getCamera() { return cam; }
	 glm::vec3& getPositon() { return Pos; };
	Action GetAction();
	void DrawUI();
	float lastActionTime = 0;
	float FOV = 90.0f;
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
	int currentlySelectedHUDSlot;
	glm::vec3 velocity;
	std::queue<Action> actionQueue;


	HUDUI* HUD = nullptr; // set just before the game starts its main loop


};
