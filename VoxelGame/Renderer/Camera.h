#pragma once

#include <glm/glm.hpp>
class Camera {
public:



	void SetPosition(glm::vec3& Position) { m_Position = Position; };
	void SetRotation(glm::vec3& Rotation) { m_Rotation = Rotation; };

	glm::vec3 GetPosition() { return m_Position; };
	glm::vec3 GetRotation() { return m_Rotation; };
	glm::mat4& GetViewMatrix() { return m_ViewMatrix; };
	glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; };

	

private:
	void UpdateMatricies();

	glm::vec3 m_Position = { 0.f,0.f,0.f };
	glm::vec3 m_Rotation = { 0.f,0.f,0.f };

	glm::mat4 m_ViewMatrix; //Move the world so it matches where the camera should be (inversed)
	glm::mat4 m_ProjectionMatrix; //Prespective

};
