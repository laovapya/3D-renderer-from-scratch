#include "Vector3.h"
#include <cmath>

Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{ }
Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{ }

Vector3 Vector3::operator+(const Vector3& other) const
{
	return {x + other.x, y + other.y, z + other.z};
}
Vector3 Vector3::operator-(const Vector3& other) const
{
	return {x - other.x, y - other.y, z - other.z};
}
Vector3 Vector3::operator-() const
{
	return {-x, -y, -z};
}
Vector3 Vector3::operator*(float scalar) const
{
	return {x * scalar, y * scalar, z * scalar};
}

float Vector3::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}
Vector3 Vector3::normalized() const
{
	float mag = magnitude();
	return mag > 0 ? (*this) * (1.0f / mag) : Vector3();
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}
Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

Vector3 operator*(float scalar, const Vector3& v)
{
	return v * scalar;
}
std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

float* Vector3::data()
{
	return &x;
}

const float* Vector3::data() const
{
	return &x;
}