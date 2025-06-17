#pragma once
#include<glad/glad.h>
#include"VBO.h"
#include"EBO.h"
//vertex array object is used by openGL to store VBO and EBO in one object, so it is easier to bind it.
class VAO
{
public:

	GLuint ID;

	VAO();


	void Link(VBO& vertices, VBO& normals, EBO& EBO);

	void Link(VBO& VBO);

	void Bind();

	void Unbind();

	void Delete();
};

