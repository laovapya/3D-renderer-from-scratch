#pragma once
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//this class manages shaders.
//using vertex shader to transform VAO's vertices using matrices, fragment shader to change the vertex color. 

class Shader {
public:
	GLuint ID;

	//separate shaders into their own files and compile them during runtime because they are not written in CPP.
	//The communication between our classes and shaders is done via uniforms - values in shader scripts that can be written to from outside the file. 
	//To write into the uniform we need its location. It is set into these fields in the constructor.
	int matrixLoc;
	int colorLoc;
	int alphaLoc;
	int projectionLoc;
	int lightColorLoc;
	int lightPosLoc;


	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();

	//Writing into the uniforms
	void SetMatrix(glm::mat4 matrix);
	void SetColor(glm::vec3 color);
	void SetAlpha(float alpha);
	void SetProjectionMatrix(glm::mat4 matrix);
	void SetLightColor(glm::vec3);
	void SetLightPosition(glm::vec3);
};