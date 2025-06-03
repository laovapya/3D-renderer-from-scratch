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

#include<vector>

//this class manages shaders.
//using vertex shader to transform VAO's vertices using matrices, fragment shader to change the vertex color. 

class Shader {
private:

public:
	GLuint ID;

	//separate shaders into their own files and compile them during runtime because they are not written in CPP.
	//The communication between our classes and shaders is done via uniforms - values in shader scripts that can be written to from outside the file. 
	//To write into the uniform we need its location. It is set into these fields in the constructor.
	int viewMatrixLoc;
	int localMatrixLoc;
	int colorLoc;
	int alphaLoc;
	int projectionLoc;
	/*int lightColorLoc;
	int lightPosLoc;*/

	int lightAmountLoc;
	int lightPositionsLoc;
	int lightColorsLoc;

	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate() const;
	void Delete() const;

	//Writing into the uniforms
	void SetViewMatrix(glm::mat4 matrix) const;
	void SetLocalMatrix(glm::mat4 matrix) const;
	void SetRenderColor(glm::vec3 color) const;
	void SetAlpha(float alpha) const;
	void SetProjectionMatrix(glm::mat4 matrix) const;


	void SetLightAmount(int amount) const;
	void SetLightColors(const std::vector<glm::vec3>& colors) const;
	void SetLightPositions(const std::vector<glm::vec3>& positions) const;
	void SetLightUniforms(int amount, const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& positions) const;
};