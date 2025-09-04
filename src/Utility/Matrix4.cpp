#include "Matrix4.h"
#include <cmath>

Matrix4::Matrix4()
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m[i][j] = (i == j) ? 1.0f : 0.0f;
}

Matrix4 Matrix4::translation(const Vector3& t)
{
	Matrix4 result;
	result.m[3][0] = t.x;
	result.m[3][1] = t.y;
	result.m[3][2] = t.z;
	return result;
}

Matrix4 Matrix4::scale(const Vector3& s)
{
	Matrix4 result;
	result.m[0][0] = s.x;
	result.m[1][1] = s.y;
	result.m[2][2] = s.z;
	return result;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 result;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			result.m[i][j] = 0;
			for(int k = 0; k < 4; k++)
				result.m[i][j] += m[i][k] * other.m[k][j];
		}
	return result;
}

Vector3 Matrix4::operator*(const Vector3& v) const
{
	float x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
	float y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
	float z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
	float w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
	if(w != 0.0f)
	{
		x /= w;
		y /= w;
		z /= w;
	}
	return {x, y, z};
}

Matrix4 Matrix4::Perspective(float fovRadians, float aspect, float nearPlane, float farPlane)
{
	Matrix4 result;
	float f = 1.0f / std::tan(fovRadians * 0.5f);
	result.m[0][0] = f / aspect;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = f;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
	result.m[2][3] = -1;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
	result.m[3][3] = 0;
	return result;
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 f = (target - eye).normalized();
	Vector3 r = Vector3::cross(f, up).normalized();
	Vector3 u = Vector3::cross(r, f);
	Matrix4 m;
	m.m[0][0] = r.x;
	m.m[0][1] = u.x;
	m.m[0][2] = -f.x;
	m.m[0][3] = 0;
	m.m[1][0] = r.y;
	m.m[1][1] = u.y;
	m.m[1][2] = -f.y;
	m.m[1][3] = 0;
	m.m[2][0] = r.z;
	m.m[2][1] = u.z;
	m.m[2][2] = -f.z;
	m.m[2][3] = 0;
	m.m[3][0] = -Vector3::dot(r, eye);
	m.m[3][1] = -Vector3::dot(u, eye);
	m.m[3][2] = Vector3::dot(f, eye);
	m.m[3][3] = 1;
	return m;
}

float* Matrix4::data()
{
	return &m[0][0];
}

const float* Matrix4::data() const
{
	return &m[0][0];
}
