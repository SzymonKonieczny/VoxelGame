#include "Player.h"
#include "Global.h"
#include "Input.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <iostream>
#include "ItemInfo.h"
#include "Renderer.h"
#include "ChunkManager.h"
Player::Player() :  Rot(45,0,0)
{



	Pos = glm::vec3(2000, 150, 2000);
	velocity = glm::vec3(0, 0, 0);
	minAABB = glm::vec3(-0.4f, -1.7f, -0.4f);
	maxAABB = glm::vec3(0.4f, 0.2f, 0.4f);



	cam.SetFarPlane(1000.f);
	cam.SetNearPlane(0.1f);

}

void Player::setItemInHUD(int ItemID)
{
	HUD->setItemStack(currentlySelectedHUDSlot, ItemStack(1, ItemID));
}

void Player::Update(float dt)
{

	HUD->Update();
	if(isInventoryOpen) Inventory->Update();
	handleRotation();
	HandleMouseButtons();
	Move(dt);

	cam.SetPosition(Pos);
	cam.SetRotation(Rot);
	cam.UpdateMatricies(FOV,screenWidth/(float)screenHeight );
}

void Player::Move(float dt)
{


	if (Input::isPressed(GLFW_KEY_C) && lastActionTime + 0.3f < glfwGetTime())
	{
		lastActionTime = glfwGetTime();

		noClip = !noClip;
	}

	if (Input::isPressed(GLFW_KEY_E) && lastActionTime + 0.3f < glfwGetTime())
	{
		lastActionTime = glfwGetTime();
		isInventoryOpen = !isInventoryOpen;
		LockMouse = !isInventoryOpen;

	}
	if (Input::isPressed(GLFW_KEY_TAB) && lastActionTime + 0.3f < glfwGetTime())
	{
		lastActionTime = glfwGetTime();
		currentlySelectedHUDSlot += 1;
		if (currentlySelectedHUDSlot >= 7) currentlySelectedHUDSlot = 0;

		HUD->setHighlight(currentlySelectedHUDSlot);
		std::cout << "Currently selected slot : " << currentlySelectedHUDSlot << std::endl;


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
		if (!noClip && isOnGround)
		{
			velocity = jumpForce * glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else if (noClip) velocity += speed * dt * glm::vec3(0.0f, 1.0f, 0.0f);

	}
	if (Input::isPressed(GLFW_KEY_LEFT_SHIFT))
	{
		velocity += speed * dt * -glm::vec3(0, 1, 0);
	}
	if (Input::isPressed(GLFW_KEY_LEFT_CONTROL))
	{
		if (noClip)speed = 100.f;
	}
	else if (Input::isReleased(GLFW_KEY_LEFT_CONTROL))
	{
		if (noClip)
			speed = 10.f;
		else
			speed = 4.f;
	}
	if (Input::isPressed(GLFW_KEY_SLASH) && lastActionTime + 0.1f < glfwGetTime())
	{
		lastActionTime = glfwGetTime();

		actionQueue.push(ActionBuilder::OpenConsoleAction());

	}
	if (!noClip) velocity.y -= 0.8f * dt;


	

}

void Player::HandleMouseButtons()
{
	if (Input::mouseIsPressed(GLFW_MOUSE_BUTTON_LEFT) && lastActionTime + 0.1f< glfwGetTime() &&LockMouse )
	{
		lastActionTime = glfwGetTime();

		actionQueue.push(ActionBuilder::BreakAction(cam.GetPosition(), cam.GetRotation(), 25));
	}
	else if (Input::mouseIsPressed(GLFW_MOUSE_BUTTON_RIGHT)&& lastActionTime + 0.1f < glfwGetTime() && LockMouse)
	{
		lastActionTime = glfwGetTime();

		if(ItemTable[HUD->ItemStacks[currentlySelectedHUDSlot].ID].CorrespondingBlock!= (int)BlockName::Air)
			actionQueue.push(ActionBuilder::PlaceAction(cam.GetPosition(), cam.GetRotation(), 25,
			(BlockName)ItemTable[HUD->ItemStacks[currentlySelectedHUDSlot].ID].CorrespondingBlock));
	}
}

void Player::GenerateUIs()
{
	HUD =  new HUDUI(glm::vec2(0.2f, 0.02f), glm::vec2(0.6f, 0.05f), glm::mat4(1));
	HUD->setItemStack(0, ItemStack(1));
	HUD->setItemStack(1, ItemStack(2));
	HUD->setItemStack(2, ItemStack(3));
	HUD->setItemStack(3, ItemStack(4));
	HUD->setItemStack(4, ItemStack(5));
	HUD->setItemStack(5, ItemStack(6));


	Inventory = new UIPlayerInventory(glm::vec2(0.3f, 0.3f), glm::vec2(0.4f, 0.4f), glm::mat4(1));
	//Inventory->SetHUDItem = [this](int ItemID) { setItemInHUD(ItemID); };//std::function<void(int)>(setItemInHUD);
	Inventory->SetHUDItem = std::bind(&Player::setItemInHUD, this, std::placeholders::_1);

}

Action Player::GetAction()	
{
	if (actionQueue.empty()) return Action(ActionType::None);
	Action ret = actionQueue.front();
	actionQueue.pop();
	return ret;
}

void Player::DrawUI()
{
	if (WindowResized)
	{
		HUD->UpdateTransformation(glm::scale(glm::mat4(1), glm::vec3(1, screenWidth / (float)screenHeight, 1)));
		//Inventory->UpdateTransformation(glm::scale(glm::mat4(1), glm::vec3( 1, screenWidth / (float)screenHeight, 1)));

		WindowResized = false;
	}
	for (auto& c : HUD->GetMeshesWithChildren())
		Renderer::SubmitUI(*c);
	
	if(isInventoryOpen)
		for (auto& c : Inventory->GetMeshesWithChildren())
			Renderer::SubmitUI(*c);

}

bool Player::handleCollisions(std::shared_ptr<ChunkManager>& chunkManager)
{
	//PointCollider::isBlockAtCollidable()
		//cant get a reference to chunkManager due to the structure
		//Maybe somehow thru the action system?

	bool didCollid = false;
	if (CheckCollisionSide(glm::vec3(velocity.x, 0, 0), chunkManager))
	{
		velocity.x = 0;
		didCollid = true;
	}
	if (CheckCollisionSide(glm::vec3(0, velocity.y, 0), chunkManager))
	{
		velocity.y = 0;
		didCollid = true;

	}
	if (CheckCollisionSide(glm::vec3(0, 0, velocity.z), chunkManager))
	{
		velocity.z = 0;
		didCollid = true;

	}

	isOnGround = CheckCollisionSide(glm::vec3(0, -0.2, 0), chunkManager);
	return didCollid;
}

bool Player::isColliding(std::shared_ptr<ChunkManager>& chunkManager)
{
	bool didCollid = false;
	didCollid |= (CheckCollisionSide(glm::vec3(velocity.x, 0, 0), chunkManager));
	

	didCollid |= (CheckCollisionSide(glm::vec3(0, velocity.y, 0), chunkManager));
	
	
	
	didCollid |= (CheckCollisionSide(glm::vec3(0, 0, velocity.z), chunkManager));


	return didCollid;
}

bool Player::CheckCollisionSide(glm::vec3 dir, std::shared_ptr<ChunkManager>& chunkManager)
{
	bool ret = false;
	glm::vec3 pointPos = Pos + minAABB;
	ret = ret|| PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager,false); // min min min


	 pointPos = Pos + glm::vec3(minAABB.x, minAABB.y, maxAABB.z);
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false); // min min max


	 pointPos = Pos + glm::vec3(minAABB.x, maxAABB.y, minAABB.z);
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false);// min max min


	 pointPos = Pos + glm::vec3(minAABB.x, maxAABB.y, maxAABB.z);
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false);// min max max

	//------------------------------------

	 pointPos = Pos + maxAABB;
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false); // min min min


	 pointPos = Pos + glm::vec3(maxAABB.x, minAABB.y, maxAABB.z);
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false); // min min max


	 pointPos = Pos + glm::vec3(maxAABB.x, maxAABB.y, minAABB.z);
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false);// min max min


	 pointPos = Pos + glm::vec3(maxAABB.x, maxAABB.y, maxAABB.z);
	ret = ret || PointCollider::isBlockAtCollidable(pointPos + dir, *chunkManager, false);// min max max

	return ret;
}

void Player::handleRotation()
{
	if (!LockMouse) return;
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
