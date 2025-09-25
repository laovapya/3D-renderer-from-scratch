#include "Object3D.h"

VAO Object3D::GetVAO() const
{
	return vao;
}

void Object3D::SetVAO(int segmentCount)
{
	vao = GenerateVAO(indexCount, segmentCount);
}

int Object3D::GetIndexCount() const
{
	return indexCount;
}

Vector3 Object3D::GetPosition() const
{
	return position;
}

Vector3 Object3D::GetScale() const
{
	return scale;
}

Object3D::Object3D()
{
	material = Material(Vector3(1.0f, 1.0f, 0.6f), 1.0f, true);
	id = idIncrement++;
}

Object3D::~Object3D()
{
	vao.Delete();
}

int Object3D::GetID() const
{
	return id;
}

int Object3D::idIncrement = 0;

void Object3D::Translate(const Vector3& v)
{
	position = position + v;
}

void Object3D::Rotate(const Vector3& eulerDelta)
{
	// eulerDelta is assumed in radians
	Quaternion deltaQuat = Quaternion(eulerDelta);
	rotation = deltaQuat * rotation;
}

void Object3D::Rotate(const float* const v)
{
	Rotate(Vector3(v[0], v[1], v[2]));
}

void Object3D::Scale(Vector3 v)
{
	float max = v.x;
	if(v.y > max)
		max = v.y;
	if(v.z > max)
		max = v.z;

	float min = v.x;
	if(v.y < min)
		min = v.y;
	if(v.z < min)
		min = v.z;

	float val = max;
	if(std::abs(min) > max)
		val = min;

	if(v.x != 0)
		v.x = val;
	if(v.y != 0)
		v.y = val;
	if(v.z != 0)
		v.z = val;

	scale = scale + v;

	if(scale.x < 0)
		scale.x = 0;
	if(scale.y < 0)
		scale.y = 0;
	if(scale.z < 0)
		scale.z = 0;
}

void Object3D::Translate(const float* const v)
{
	Translate(Vector3(v[0], v[1], v[2]));
}

void Object3D::Scale(const float* const v)
{
	Scale(Vector3(v[0], v[1], v[2]));
}

const Matrix4 Object3D::GetModelMatrix() const
{
	Matrix4 translation = Matrix4::translation(position);
	Matrix4 rotationM = Matrix4::Rotate(rotation);
	Matrix4 scaling = Matrix4::scale(scale);

	return scaling * rotationM * translation; //ensure correct order based on the Matrix4 * operator
}

// Vector3 Object3D::GetBorderColor() const
// {
// 	return selectColor;
// }

// Vector3 Object3D::GetColor() const
// {
// 	return material.color;
// }

Object3D::type Object3D::GetType() const
{
	return objectType;
}

// const Vector3 Object3D::selectColor = Vector3(0.0f, 0.3f, 0.65f); // blue

// bool Object3D::GetIfLit() const
// {
// 	return material.isLit;
// }

// void Object3D::SetColor(const Vector3& color)
// {
// 	material.color = color;
// }

// void Object3D::SetColor(const Vector3& color, float alpha)
// {
// 	material.color = color;
// 	material.colorAlpha = alpha;
// }
// void Object3D::SetColor(float r, float g, float b, float alpha)
// {
// 	material.color = Vector3(r, g, b);
// 	material.colorAlpha = alpha;
// }
Material& Object3D::GetMaterial()
{
	return material;
}

void Object3D::SetSelected(bool selected)
{
	isSelected = selected;
}

bool Object3D::GetIfSelected() const
{
	return isSelected;
}

std::vector<float> Object3D::CalculateNormals(const std::vector<float>& vertices,
											  const std::vector<int>& indices) const
{
	std::vector<Vector3> normalsVec(vertices.size() / 3, Vector3(0.0f, 0.0f, 0.0f));

	for(size_t i = 0; i < indices.size(); i += 3)
	{
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		Vector3 v0(vertices[i0 * 3], vertices[i0 * 3 + 1], vertices[i0 * 3 + 2]);
		Vector3 v1(vertices[i1 * 3], vertices[i1 * 3 + 1], vertices[i1 * 3 + 2]);
		Vector3 v2(vertices[i2 * 3], vertices[i2 * 3 + 1], vertices[i2 * 3 + 2]);

		Vector3 edge1 = v1 - v0;
		Vector3 edge2 = v2 - v0;

		Vector3 faceNormal = -Vector3::cross(edge1, edge2).normalized();

		normalsVec[i0] += faceNormal;
		normalsVec[i1] += faceNormal;
		normalsVec[i2] += faceNormal;
	}

	std::vector<float> normals;
	normals.reserve(vertices.size());

	for(auto& normal : normalsVec)
	{
		Vector3 n = normal.normalized();
		normals.push_back(n.x);
		normals.push_back(n.y);
		normals.push_back(n.z);
	}

	return normals;
}
