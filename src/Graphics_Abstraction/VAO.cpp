#include"VAO.h"
#include"EBO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}


void VAO::Link(VBO& vertices, VBO& normals, EBO& EBO)
{
	Bind();
	EBO.Bind();
		vertices.Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //position vectors
		glEnableVertexAttribArray(0);
		//vertices.Unbind();
		normals.Bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //normal vectors
		glEnableVertexAttribArray(1);
		//normals.Unbind();
	Unbind();

	
	EBO.Unbind();
}
void VAO::Link(VBO& vbo) { //no normals, no indices 
	Bind();
	vbo.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
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