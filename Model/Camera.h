#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	const glm::vec3 worldUp = glm::vec3(0, 1, 0);

	Camera();

	//base transform fields
	glm::vec3 position;
	glm::vec3 target;


	glm::mat4 projection;


	//view matrix is a camera transformation matrix applied to all objects. 
	glm::mat4 view;


	float panSpeed = 10;
	float orbitSpeed = 10;

	//camera's coordinate system
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
public:
	Camera(const Camera&) = delete;
	static Camera& GetInstance() {
		static Camera instance;
		return instance;
	}
	static glm::mat4 GetViewMatrix();
	static glm::mat4 GetProjectionMatrix();


	//functionality to move the camera along the screen plane
	static void Pan(glm::vec3);
	//functionality to orbit the camera around its target (starts at 0,0,0) 
	void Orbit(glm::vec3 angle);

	static void SetProjectionMatrix();



	static glm::vec3 GetRight();
	static glm::vec3 GetUp();
	static glm::vec3 GetForward();
};
