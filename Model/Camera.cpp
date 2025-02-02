#include "Camera.h"
#include"DeltaTime.h"
#include"Window.h"
Camera::Camera() {

	position = glm::vec3(10, 8, 15);
	target = glm::vec3(0, 0, 0);


	projection = glm::perspective(glm::radians(45.0f), Window::GetAspectRatio(), 0.1f, 100.0f);
	view = glm::lookAt(position, target, glm::vec3(0, 1, 0));

	//cameraRight = glm::vec3(1, 0, 0);

	forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(worldUp, forward));
	up = glm::normalize(glm::cross(right, forward));
}
void Camera::SetProjectionMatrix() {
	GetInstance().projection = glm::perspective(glm::radians(45.0f), Window::GetAspectRatio(), 0.1f, 100.0f);
}
glm::mat4 Camera::GetViewMatrix() {
	return GetInstance().view;
}

glm::mat4 Camera::GetProjectionMatrix() {
	return GetInstance().projection;
}

void Camera::Pan(glm::vec3 v) {
	Camera& instance = Camera::GetInstance();

	instance.forward = instance.target - instance.position;
	instance.right = glm::normalize(glm::cross(instance.worldUp, instance.forward));
	instance.up = glm::normalize(glm::cross(instance.right, instance.forward));
	float speed = instance.panSpeed * instance.forward.length();

	instance.forward = glm::normalize(instance.forward);

	instance.position += (instance.right * v.x + instance.up * v.y + instance.forward * v.z) * speed;
	instance.target += (instance.right * v.x + instance.up * v.y) * speed;

	instance.view = glm::lookAt(instance.position, instance.target, instance.worldUp);
}

void Camera::Orbit(glm::vec3 angle) {
	//target.y = 0;
	Camera& instance = Camera::GetInstance();

	angle *= orbitSpeed;
	glm::vec4 v1 = glm::vec4(position.x, position.y, position.z, 1);
	glm::mat4 rotateWorldUp = glm::rotate(glm::mat4(1), angle.y, worldUp);

	v1 = rotateWorldUp * v1;

	//glm::vec3 temp = target - position;
	instance.forward = target - position;
	instance.right = glm::cross(worldUp, instance.forward);
	instance.up = glm::normalize(glm::cross(instance.right, instance.forward));

	glm::mat4 rotateCameraRight = glm::rotate(glm::mat4(1), angle.x, instance.right);
	glm::vec4 temp = rotateCameraRight * v1;
	if (abs(glm::normalize(temp).y) < 0.99)
		v1 = temp;



	position.x = v1.x;
	position.y = v1.y;
	position.z = v1.z;

	view = glm::lookAt(position, target, worldUp);
}

//glm::vec3 Camera::GetMouseVector() {
//	glm::vec3 mouseVector = 
//}
glm::vec3 Camera::GetRight() {
	return glm::normalize(GetInstance().right);
}
glm::vec3 Camera::GetUp() {
	return glm::normalize(GetInstance().up);
}
glm::vec3 Camera::GetForward() {
	return glm::normalize(GetInstance().forward);
}