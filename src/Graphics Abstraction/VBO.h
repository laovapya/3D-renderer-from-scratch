#pragma once
#include<glad/glad.h>

//vertex buffer object is used by openGL to bind vertices and related information.
class VBO
{
public:

	GLuint ID;

	VBO(float* vertices, GLsizeiptr size);


	void Bind();

	void Unbind();

	void Delete();
};