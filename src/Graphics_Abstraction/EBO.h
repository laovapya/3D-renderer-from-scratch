#pragma once
#include<glad/glad.h>

//element buffer object is used by openGL to bind indices and related information.
class EBO
{
public:

	GLuint ID;

	EBO(int* indices, GLsizeiptr size);

	void Bind();

	void Unbind();

	void Delete();
};
