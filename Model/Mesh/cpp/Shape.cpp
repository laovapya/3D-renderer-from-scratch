#include "Shape.h"

glm::vec3 Shape::GetPosition() {
	return position;
}

glm::vec3 Shape::GetRotation() {
	return rotation;
}

glm::vec3 Shape::GetScale() {
	return scale;
}

Shape::Shape() {
	id = idIncrement++;
}

int Shape::GetID() {
	return id;
}

int Shape::idIncrement = 0;

void Shape::Translate(glm::vec3 v) {
	position = position + v;
}

void Shape::Rotate(glm::vec3 v) {
	rotation = position + v;
}

void Shape::Scale(glm::vec3 v) {
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

void Shape::Translate(float* v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
	Translate(v1);
}

void Shape::Rotate(float* v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]) * VertexData::degToRad;
	Rotate(v1);
}

void Shape::Scale(float* v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
	Scale(v1);
}

glm::mat4 Shape::GetObjectMatrix(Shape* object) {

	glm::mat4 m1 = glm::translate(glm::mat4(1.0f), object->GetPosition());

	glm::mat4 m2 = glm::rotate(glm::mat4(1.0f), object->GetRotation().x, glm::vec3(1, 0, 0));
	glm::mat4 m3 = glm::rotate(glm::mat4(1.0f), object->GetRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 m4 = glm::rotate(glm::mat4(1.0f), object->GetRotation().z, glm::vec3(0, 0, 1));

	glm::mat4 m5 = glm::scale(glm::mat4(1.0f), object->GetScale());

	glm::mat4 a = m4 * m5;
	a = m3 * a;
	a = m2 * a;
	a = m1 * a;

	return a;
}

int Shape::GetIndexCount() {
	return indexCount;
}

glm::vec3 Shape::GetColor() {
	if (isSelected)
		return selectedColor;
	return normalColor;
}

Shape::Shapes Shape::GetShape() {
	return shape;
}