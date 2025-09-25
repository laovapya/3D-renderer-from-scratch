#include "Camera.h"

Camera::Camera()
{
	position = Vector3(10, 8, 15);
	target = Vector3(0, 0, 0);

	forward = (target - position).normalized();
	right = Vector3::cross(worldUp, forward).normalized();
	up = Vector3::cross(right, forward).normalized();

	view = Matrix4::LookAt(position, target, worldUp);
}

Matrix4 Camera::GetViewMatrix() const
{
	return view;
}

void Camera::Pan(Vector3 v)
{
	forward = (target - position).normalized();
	right = Vector3::cross(worldUp, forward).normalized();
	up = Vector3::cross(right, forward).normalized();

	float distance = (target - position).magnitude();
	float speed = panSpeed * distance * 0.1f;
	Vector3 offset = (right * v.x + up * v.y + forward * v.z) * speed;
	position += offset;
	target += (right * v.x + up * v.y) * speed;

	view = Matrix4::LookAt(position, target, worldUp);
}

void Camera::Orbit(Vector3 angle) // orbit around target
{
	angle *= orbitSpeed;

	Vector3 relPos = position - target;

	Quaternion q(angle);

	relPos = q * relPos;

	position = target + relPos;

	forward = (target - position).normalized();
	right = Vector3::cross(worldUp, forward).normalized();
	up = Vector3::cross(forward, right).normalized();

	view = Matrix4::LookAt(position, target, worldUp);
}

Vector3 Camera::GetRight() const
{
	return right.normalized();
}

Vector3 Camera::GetUp() const
{
	return up.normalized();
}

Vector3 Camera::GetForward() const
{
	return forward.normalized();
}
