#include "Camera.h"
#include"DeltaTime.h"
#include"Window.h"
Camera::Camera() {

	position = glm::vec3(10, 8, 15); //temporary start position 
	target = glm::vec3(0, 0, 0); //temporary target 



	view = glm::lookAt(position, target, glm::vec3(0, 1, 0));

	forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(worldUp, forward));
	up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::GetViewMatrix() {
	return view;
}



void Camera::Pan(glm::vec3 v) {
    forward = target - position;
    right = glm::normalize(glm::cross(worldUp, forward));
    up = glm::normalize(glm::cross(right, forward));
    float speed = panSpeed * forward.length();

    forward = glm::normalize(forward);

    position += (right * v.x + up * v.y + forward * v.z) * speed;
    target += (right * v.x + up * v.y) * speed;

    view = glm::lookAt(position, target, worldUp);
}

void Camera::Orbit(glm::vec3 angle) {
    angle *= orbitSpeed;
    glm::vec4 v1 = glm::vec4(position.x, position.y, position.z, 1);
    glm::mat4 rotateWorldUp = glm::rotate(glm::mat4(1), angle.y, worldUp);

    v1 = rotateWorldUp * v1;

    forward = target - position;
    right = glm::cross(worldUp, forward);
    up = glm::normalize(glm::cross(right, forward));

    glm::mat4 rotateCameraRight = glm::rotate(glm::mat4(1), angle.x, right);
    glm::vec4 temp = rotateCameraRight * v1;
    if (abs(glm::normalize(temp).y) < 0.99)
        v1 = temp;

    position.x = v1.x;
    position.y = v1.y;
    position.z = v1.z;

    view = glm::lookAt(position, target, worldUp);
}

glm::vec3 Camera::GetRight() {
    return glm::normalize(right);
}

glm::vec3 Camera::GetUp() {
    return glm::normalize(up);
}

glm::vec3 Camera::GetForward() {
    return glm::normalize(forward);
}