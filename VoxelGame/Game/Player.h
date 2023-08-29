#pragma once
#include "../Renderer/Camera.h"

class Player {

public:
	Player();
	void Update(float dt);
	void Move();
	Camera& getCamera() { return cam; }
private:
	void handleRotation();
	float sensitivity = 60;
	float speed = 2;
	Camera cam;
	glm::vec3 Pos;
	glm::vec3 Rot;


};
