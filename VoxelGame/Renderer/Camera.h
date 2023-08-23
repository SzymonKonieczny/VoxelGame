#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera {
public:



	void SetPosition(glm::vec3& Position) { m_Position = Position; };
	void SetRotation(glm::vec3& Rotation) { m_Rotation = Rotation; };

	void SetPosition(const glm::vec3& Position) { m_Position = Position; };
	void SetRotation(const glm::vec3& Rotation) { m_Rotation = Rotation; };
	glm::vec3 GetPosition() { return m_Position; };
	glm::vec3 GetRotation() { return m_Rotation; };
	glm::mat4& GetViewMatrix() { return m_ViewMatrix; };
	glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; };

	

	void UpdateMatricies() {

		m_ViewMatrix = glm::lookAt(m_Position, m_Position+m_Rotation, { 0,1,0 });
		//m_ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.1, -2.f));
		m_ProjectionMatrix = glm::perspective(glm::radians(60.f), 1.f, 0.1f, 100.f);
	}
private:

	glm::vec3 m_Position = { 0.f,0.f,0.f };
	glm::vec3 m_Rotation = { 0.f,0.f,0.f };

	glm::mat4 m_ViewMatrix; //Move the world so it matches where the camera should be (inversed)
	glm::mat4 m_ProjectionMatrix; //Prespective

};
