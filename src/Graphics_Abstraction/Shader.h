#pragma once
#include <glad/glad.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Matrix4.h"
#include "TextureManager.h"
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
	int modelMatrixLoc;
	int colorLoc;
	int alphaLoc;
	int projectionLoc;
	int lightAmountLoc;
	int lightPositionsLoc;
	int lightColorsLoc;
	int textureSamplerLoc;

	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate() const;
	void Delete() const;

	// write into uniforms
	void SetViewMatrix(const Matrix4& matrix) const;
	void SetModelMatrix(const Matrix4& matrix) const;
	void SetRenderColor(const Vector3& color) const;
	void SetAlpha(float alpha) const;
	void SetProjectionMatrix(const Matrix4& matrix) const;

	void SetLightAmount(int amount) const;
	void SetLightColors(const std::vector<Vector3>& colors) const;
	void SetLightPositions(const std::vector<Vector3>& positions) const;
	void SetLightUniforms(int amount,
						  const std::vector<Vector3>& colors,
						  const std::vector<Vector3>& positions) const;

	void ActivateTexture(GLuint textureID, GLuint unit) const;
};
