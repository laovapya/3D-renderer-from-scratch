#pragma once
#include <cerrno>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Matrix4.h"
#include "Vector3.h"

// this class manages shaders.
// vertex shader transforms VAO vertices using matrices
// fragment shader changes vertex color

class Shader
{
private:
public:
	GLuint ID;

	// uniform locations
	int viewMatrixLoc;
	int localMatrixLoc;
	int colorLoc;
	int alphaLoc;
	int projectionLoc;
	int lightAmountLoc;
	int lightPositionsLoc;
	int lightColorsLoc;

	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate() const;
	void Delete() const;

	// write into uniforms
	void SetViewMatrix(const Matrix4& matrix) const;
	void SetLocalMatrix(const Matrix4& matrix) const;
	void SetRenderColor(const Vector3& color) const;
	void SetAlpha(float alpha) const;
	void SetProjectionMatrix(const Matrix4& matrix) const;

	void SetLightAmount(int amount) const;
	void SetLightColors(const std::vector<Vector3>& colors) const;
	void SetLightPositions(const std::vector<Vector3>& positions) const;
	void SetLightUniforms(int amount,
						  const std::vector<Vector3>& colors,
						  const std::vector<Vector3>& positions) const;
};
