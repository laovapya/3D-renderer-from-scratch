#pragma once

#include"VAO.h"
#include"VertexData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp> 

#include"math.h"


//The parent 3D object abstract class 

class Object3D
{


public:
	std::string name;

	enum type {
		cube,
		cone,
		cylinder,
		sphere,

		lightsource,
		camera
	};

	Object3D();
	~Object3D();

	virtual VAO GenerateVAO(int& indexCount, int segmentCount = 12) const = 0; 
	int GetIndexCount() const;
	void SetVAO(int segmentCount);
	VAO GetVAO() const;


	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	int GetID() const;

	void Translate(const glm::vec3& v);
	void Rotate(const glm::vec3& v);
	virtual void Scale(glm::vec3 v);

	void Translate(const float* const v);
	void Rotate(const float* const v);
	virtual void Scale(const float* const v);

	void SetSelected(bool selected);
	bool GetIfSelected() const;

	//The translation, rotation and scaling transformations are done using matrices.
	//We multiply each vertex in the VAO by a matrix to get the result. 
	//The matrix is constructed using the position, rotation, scale fields.

	glm::mat4 GetObjectMatrix() const;


	glm::vec3 GetBorderColor() const;
	glm::vec3 GetColor() const;
	void SetColor(const glm::vec4& color);
	void SetColor(const glm::vec3& color);
	type GetType() const;

	//return the shape's corresponding VAO using VertexData methods. 

	//whether the object is selected in the object list menu.

	const static glm::vec3 selectColor; 	//Color outline displayed when an object is selected (blue) 

	bool GetIfLit() const; //whether to use lit shader

protected:
	std::vector<float> CalculateNormals(const std::vector<float>& vertices, const std::vector<int>& indices) const;


	type objectType;
	bool isLit = true; //whether to use lit shader 


	glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.6f); //The object color (pale yellow) 
	float colorAlpha;

private:
	int id; //id is used to link the object with a value in the UI object list menu.
	static int idIncrement;



	bool isSelected = false;  //to another class 


	VAO vao;//VAO (vertex array object) stores vertex and index data, which is used to render 3D objects.
	int indexCount; //count of index in the VAO. Set while generating VAO. 


	//transformation fields. The rotation is in radians around X, Y, Z axes.
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);



};