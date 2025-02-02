#include"VAO.h"
#include"EBO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}


void VAO::Link(VBO& VBO, EBO& EBO)
{
	Bind();
	VBO.Bind();
	EBO.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	VBO.Unbind();
	Unbind();
	EBO.Unbind();
}
void VAO::Link(VBO& vbo) {
	Bind();
	vbo.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	vbo.Unbind();
	Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}