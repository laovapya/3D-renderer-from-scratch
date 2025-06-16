#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	const glm::vec3 worldUp = glm::vec3(0, 1, 0);

	glm::vec3 position;
	glm::vec3 target;

	
	glm::mat4 view;

	float panSpeed = 10;
	float orbitSpeed = 10;

	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;

public:
	Camera();

	glm::mat4 GetViewMatrix() const;
	

	void Pan(glm::vec3);
	void Orbit(glm::vec3 angle);
	

	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetForward() const;

};