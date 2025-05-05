#include "Object3D.h"

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

int Object3D::GetID() const {
	return id;
}

int Object3D::idIncrement = 0;

void Object3D::Translate(const glm::vec3& v) {
	position = position + v;
}

void Object3D::Rotate(const glm::vec3& v) {
	rotation = position + v;
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
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]) * VertexData::degToRad;
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

int Object3D::GetIndexCount() const {
	return indexCount;
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