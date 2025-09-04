#pragma once
#include <iostream>

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-() const;
	Vector3 operator*(float scalar) const;

	float magnitude() const;
	Vector3 normalized() const;

	static float dot(const Vector3& a, const Vector3& b);
	static Vector3 cross(const Vector3& a, const Vector3& b);

	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scalar);

	bool operator==(const Vector3& other) const;

	float* data();
	const float* data() const;
};

Vector3 operator*(float scalar, const Vector3& v);
std::ostream& operator<<(std::ostream& os, const Vector3& v);
