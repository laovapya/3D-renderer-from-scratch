#pragma once

#include "VAO.h"
#include "VertexData.h"

#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

//The parent 3D object abstract class

class Object3D
{
public:
	enum type
	{
		cube,
		cone,
		cylinder,
		sphere,

		lightsource,
		camera
	};

private:
	int id; //id is used to link the object with a value in the UI object list menu.
	static int idIncrement;

	bool isSelected = false;

	VAO vao; //VAO (vertex array object) stores vertex and index data, which is used to render 3D objects.
	int indexCount; //count of index in the VAO. Set while generating VAO.

	//transformation fields. The rotation is in radians around X, Y, Z axes.
	Vector3 position = Vector3(0, 0, 0);
	Quaternion rotation = Quaternion(1, 0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);

protected:
	virtual VAO GenerateVAO(int& indexCount, int segmentCount = 12) const = 0;

	void SetVAO(int segmentCount);
	std::vector<float> CalculateNormals(const std::vector<float>& vertices,
										const std::vector<int>& indices) const;

	type objectType;
	bool isLit = true; //whether to use lit shader

	Vector3 color = Vector3(1.0f, 1.0f, 0.6f); //The object color (pale yellow)
	float colorAlpha;

public:
	std::string name;

	Object3D();
	~Object3D();

	int GetIndexCount() const;
	VAO GetVAO() const;

	Vector3 GetPosition() const;
	Vector3 GetScale() const;

	int GetID() const;

	void Translate(const Vector3& v);
	void Rotate(const Vector3& v);
	virtual void Scale(Vector3 v);

	void Translate(const float* const v);
	void Rotate(const float* const v);
	virtual void Scale(const float* const v);

	void SetSelected(bool selected);
	bool GetIfSelected() const;

	//The translation, rotation and scaling transformations are done using matrices.
	//We multiply each vertex in the VAO by a matrix to get the result.
	//The matrix is constructed using the position, rotation, scale fields.

	Matrix4 GetObjectMatrix() const;

	Vector3 GetBorderColor() const;
	Vector3 GetColor() const;
	void SetColor(const Vector3& color);
	void SetColor(const Vector3& color, float alpha);
	void SetColor(float r, float g, float b, float alpha);
	type GetType() const;

	//whether the object is selected in the object list menu.

	const static Vector3 selectColor; //Color outline displayed when an object is selected (blue)

	bool GetIfLit() const; //whether to use lit shader
};
