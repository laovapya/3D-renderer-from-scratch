#pragma once
#include "Utility/Matrix4.h"
#include "Utility/Quaternion.h"
#include "Utility/Vector3.h"
class Camera
{
private:
	const Vector3 worldUp = Vector3(0, 1, 0);

	Vector3 position;
	Vector3 target;

	Matrix4 view;

	float panSpeed = 10;
	float orbitSpeed = 10;

	Vector3 right;
	Vector3 up;
	Vector3 forward;

public:
	Camera();

	Matrix4 GetViewMatrix() const;

	void Pan(Vector3 offset);
	void Orbit(Vector3 angle);

	Vector3 GetRight() const;
	Vector3 GetUp() const;
	Vector3 GetForward() const;
};
