#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion()
	: w(1)
	, x(0)
	, y(0)
	, z(0)
{ }
Quaternion::Quaternion(float w, float x, float y, float z)
	: w(w)
	, x(x)
	, y(y)
	, z(z)
{ }
Quaternion::Quaternion(const Vector3& eulerAngles)
{
	float cx = std::cos(eulerAngles.x * 0.5f);
	float sx = std::sin(eulerAngles.x * 0.5f);
	float cy = std::cos(eulerAngles.y * 0.5f);
	float sy = std::sin(eulerAngles.y * 0.5f);
	float cz = std::cos(eulerAngles.z * 0.5f);
	float sz = std::sin(eulerAngles.z * 0.5f);

	w = cx * cy * cz + sx * sy * sz;
	x = sx * cy * cz - cx * sy * sz;
	y = cx * sy * cz + sx * cy * sz;
	z = cx * cy * sz - sx * sy * cz;
}

Quaternion Quaternion::fromAxisAngle(const Vector3& axis, float angleRad)
{
	Vector3 v = axis.normalized();
	float halfAngle = angleRad * 0.5f;
	float sine = std::sin(halfAngle);
	return Quaternion(std::cos(halfAngle), v.x * sine, v.y * sine, v.z * sine);
}

Quaternion Quaternion::normalized() const
{
	float len = std::sqrt(w * w + x * x + y * y + z * z);
	return (len > 0.0f) ? Quaternion(w / len, x / len, y / len, z / len) : Quaternion();
}

Quaternion Quaternion::operator*(const Quaternion& o) const
{
	return Quaternion(w * o.w - x * o.x - y * o.y - z * o.z,
					  w * o.x + x * o.w + y * o.z - z * o.y,
					  w * o.y - x * o.z + y * o.w + z * o.x,
					  w * o.z + x * o.y - y * o.x + z * o.w);
}

Vector3 Quaternion::operator*(const Vector3& v) const
{
	Quaternion qv(0, v.x, v.y, v.z);

	Quaternion qConj(w, -x, -y, -z); // conjugate
	Quaternion qr = (*this) * qv * qConj;

	return Vector3(qr.x, qr.y, qr.z);
}

Matrix4 Quaternion::toMatrix4() const
{
	Quaternion q = this->normalized();

	float xx = q.x * q.x;
	float yy = q.y * q.y;
	float zz = q.z * q.z;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float yz = q.y * q.z;
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;

	Matrix4 m;
	m.m[0][0] = 1.0f - 2.0f * (yy + zz);
	m.m[0][1] = 2.0f * (xy - wz);
	m.m[0][2] = 2.0f * (xz + wy);

	m.m[1][0] = 2.0f * (xy + wz);
	m.m[1][1] = 1.0f - 2.0f * (xx + zz);
	m.m[1][2] = 2.0f * (yz - wx);

	m.m[2][0] = 2.0f * (xz - wy);
	m.m[2][1] = 2.0f * (yz + wx);
	m.m[2][2] = 1.0f - 2.0f * (xx + yy);

	return m;
}
