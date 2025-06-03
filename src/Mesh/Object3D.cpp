#include "Object3D.h"

VAO Object3D::GetVAO() const {
	return vao;
}
void Object3D::SetVAO(int segmentCount) {
	vao = GenerateVAO(indexCount, segmentCount);
}
int Object3D::GetIndexCount() const {
	return indexCount;
}


glm::vec3 Object3D::GetPosition() const {
	return position;
}

glm::vec3 Object3D::GetRotation() const {
	return rotation;
}

glm::vec3 Object3D::GetScale() const{
	return scale;
}

Object3D::Object3D() {
	id = idIncrement++;

}
Object3D::~Object3D() {
	vao.Delete();
}

int Object3D::GetID() const {
	return id;
}

int Object3D::idIncrement = 0;

void Object3D::Translate(const glm::vec3& v) {
	position = position + v;
}

void Object3D::Rotate(const glm::vec3& v) {
	rotation = rotation + v;
}

void Object3D::Scale(glm::vec3 v) {
	float max = v.x;

	if (v.y > max)
		max = v.y;
	if (v.z > max)
		max = v.z;

	float min = v.x;
	if (v.y < min)
		min = v.y;
	if (v.z < min)
		min = v.z;

	float val = max;
	if (abs(min) > max)
		val = min;

	if (v.x != 0)
		v.x = val;
	if (v.y != 0)
		v.y = val;
	if (v.z != 0)
		v.z = val;

	scale = scale + v;

	if (scale.x < 0)
		scale.x = 0;
	if (scale.y < 0)
		scale.y = 0;
	if (scale.z < 0)
		scale.z = 0;
}

void Object3D::Translate(const float* const v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
	Translate(v1);
}

void Object3D::Rotate(const float* const v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]) * 3.14159265359f / 180.0f; 
	Rotate(v1);
}

void Object3D::Scale(const float* const v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
	Scale(v1);
}

glm::mat4 Object3D::GetObjectMatrix() const {
	glm::mat4 m1 = glm::translate(glm::mat4(1.0f), GetPosition());

	glm::vec3 rotation = GetRotation();  
	glm::quat qx = glm::quat(glm::vec3(rotation.x, 0, 0)); 
	glm::quat qy = glm::quat(glm::vec3(0, rotation.y, 0)); 
	glm::quat qz = glm::quat(glm::vec3(0, 0, rotation.z));
	glm::mat4 m2 = glm::mat4_cast(qz * qy * qx);


	glm::mat4 m3 = glm::scale(glm::mat4(1.0f), GetScale());

	glm::mat4 a = m1 * (m2 * m3);

	return a;
}



glm::vec3 Object3D::GetBorderColor() const { //to another class 
	return selectColor;
}
glm::vec3 Object3D::GetColor() const { //to another class 

	return color;
}

Object3D::type Object3D::GetType() const {
	return objectType;
}

const glm::vec3 Object3D::selectColor = glm::vec3(0.0f, 0.3f, 0.65f); //blue 

bool Object3D::GetIfLit() const {
	return isLit;
}

void Object3D::SetColor(const glm::vec3& color){
	this->color = color;
}

void Object3D::SetColor(const glm::vec4& color) {
    this->color = glm::vec3(color);  
    this->colorAlpha = color.a;      
}

void Object3D::SetSelected(bool selected) {
	isSelected = selected;

}
bool Object3D::GetIfSelected() const {
	return isSelected;
}

// Calculates normals for a triangle mesh using cross products
std::vector<float> Object3D::CalculateNormals(const std::vector<float>& vertices, const std::vector<int>& indices) const
{
	std::vector<glm::vec3> normalsVec3(vertices.size() / 3, glm::vec3(0.0f));

	// each triangle
	for (size_t i = 0; i < indices.size(); i += 3) {
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		glm::vec3 v0(vertices[i0 * 3], vertices[i0 * 3 + 1], vertices[i0 * 3 + 2]);
		glm::vec3 v1(vertices[i1 * 3], vertices[i1 * 3 + 1], vertices[i1 * 3 + 2]);
		glm::vec3 v2(vertices[i2 * 3], vertices[i2 * 3 + 1], vertices[i2 * 3 + 2]);

		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v0;

		glm::vec3 faceNormal = -glm::normalize(glm::cross(edge1, edge2));

		normalsVec3[i0] += faceNormal;
		normalsVec3[i1] += faceNormal;
		normalsVec3[i2] += faceNormal;
	}

	std::vector<float> normals;
	normals.reserve(vertices.size());

	for (auto& normal : normalsVec3) {
		glm::vec3 normalized = glm::normalize(normal);
		normals.push_back(normalized.x);
		normals.push_back(normalized.y);
		normals.push_back(normalized.z);
	}

	return normals;
}
