#pragma once

#include"VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"VertexData.h"

//The parent 3D object abstract class 

class Shape
{
protected:
	//transformation fields. The rotation is in radians around X, Y, Z axes.
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	//The object color (grey)
	glm::vec3 normalColor = glm::vec3(0.5f, 0.5f, 0.5f);
	//Color displayed when an object is selected (blue)
	glm::vec3 selectedColor = glm::vec3(0.0f, 0.3f, 0.65f);

	//id is used to link the object with a value in the UI object list menu.
	int id;
	static int idIncrement;

	//count of index in the VAO. Retrieved from VertexData class
	int indexCount = 0;


public:
	enum Shapes {
		cube,
		cone,
		cylinder,
		sphere
	};

	Shape();

	int GetIndexCount();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	int GetID();

	//Add transform vector to current
	void Translate(glm::vec3 v);
	void Rotate(glm::vec3 v);
	void Scale(glm::vec3 v);

	void Translate(float* v);
	void Rotate(float* v);
	void Scale(float* v);

	//The translation, rotation and scaling transformations are done using matrices.
	//We multiply each vertex in the VAO by a matrix to get the result. 
	//The matrix is constructed using the position, rotation, scale fields.
	static glm::mat4 GetObjectMatrix(Shape* object);

	//whether the object is selected in the object list menu.
	bool isSelected = false;

	glm::vec3 GetColor();
	Shapes GetShape();

	//return the shape's corresponding VAO using VertexData methods. 
	virtual VAO GetVAO() = 0;

protected:
	Shapes shape;
};