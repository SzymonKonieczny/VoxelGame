#pragma once
#include "../Renderer/Camera.h"
#include "Action.h"
#include "PointCollider.h"
#include "BlockInfo.h"
#include "PointCollider.h"
#include <queue>
#include "UI/UIHUD.h"
#include "UI/UIPlayerInventory.h"
#include "IEntity.h"
class ChunkManager;
class Player : public IEntity{

public:
	Player();
	void setItemInHUD(int ItemID);
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
	bool noClip = true;
	void handleCollisions(std::shared_ptr<ChunkManager>& chunkManager);
	float drag = 0.2f;
private:
	bool CheckCollisionSide(glm::vec3 dir, std::shared_ptr<ChunkManager>& chunkManager);
	bool isInventoryOpen = false;
	bool LockMouse = true;
	void handleRotation();
	Camera cam;
	glm::vec3 Rot;
	bool isOnGround=false;
	float speed = 0.1f;

	float sensitivity = 100.0f;
	float jumpForce = 0.2f;
	float BlocksCooldown = 0.1;
	int currentlySelectedHUDSlot;
	std::queue<Action> actionQueue;


	HUDUI* HUD = nullptr; // set just before the game starts its main loop
	UIPlayerInventory* Inventory = nullptr;


};
