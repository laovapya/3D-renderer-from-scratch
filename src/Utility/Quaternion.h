#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class Quaternion
{
public:
	float w, x, y, z;

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(const Vector3& eulerAngles);

	static Quaternion fromAxisAngle(const Vector3& axis, float angleRad);

	Quaternion normalized() const;

	Quaternion operator*(const Quaternion& other) const;
	Vector3 operator*(const Vector3& v) const;
};