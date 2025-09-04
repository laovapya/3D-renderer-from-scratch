#pragma once
#include "Vector3.h"

class Matrix4
{
public:
	float m[4][4];

	Matrix4();

	static Matrix4 translation(const Vector3& t);
	static Matrix4 scale(const Vector3& s);

	Matrix4 operator*(const Matrix4& other) const;
	Vector3 operator*(const Vector3& v) const; // assumes w=1

	static Matrix4 Perspective(float fov, float aspect, float nearPlane, float farPlane);
	static Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

	float* data();
	const float* data() const;
};
