#include "shader.h"
#include <fstream>
#include <iostream>

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if(in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	std::cout << filename << " wrong shader file path" << std::endl;
	throw(errno);
}

Shader::Shader()
	: ID(-1)
{ }

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	viewMatrixLoc = glGetUniformLocation(ID, "viewMatrix");
	modelMatrixLoc = glGetUniformLocation(ID, "modelMatrix");
	colorLoc = glGetUniformLocation(ID, "color");
	alphaLoc = glGetUniformLocation(ID, "alpha");
	projectionLoc = glGetUniformLocation(ID, "projection");
	lightAmountLoc = glGetUniformLocation(ID, "lightAmount");
	lightPositionsLoc = glGetUniformLocation(ID, "lightPositions");
	lightColorsLoc = glGetUniformLocation(ID, "lightColors");
	textureSamplerLoc = glGetUniformLocation(ID, "textureSampler");
}

void Shader::Activate() const
{
	glUseProgram(ID);
}
void Shader::Delete() const
{
	glDeleteProgram(ID);
}

void Shader::SetProjectionMatrix(const Matrix4& matrix) const
{
	if(projectionLoc == -1)
	{
		std::cout << "Failed to find projection uniform\n";
		return;
	}
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, matrix.data());
}

void Shader::SetViewMatrix(const Matrix4& matrix) const
{
	if(viewMatrixLoc == -1)
	{
		std::cout << "Failed to find view matrix uniform\n";
		return;
	}
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, matrix.data());
}

void Shader::SetModelMatrix(const Matrix4& matrix) const
{
	if(modelMatrixLoc == -1)
	{
		std::cout << "Failed to find local matrix uniform\n";
		return;
	}
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, matrix.data());
}

void Shader::SetRenderColor(const Vector3& color) const
{
	if(colorLoc == -1)
	{
		std::cout << "Failed to find color uniform\n";
		return;
	}
	glUniform3fv(colorLoc, 1, color.data());
}

void Shader::SetAlpha(float alpha) const
{
	if(alphaLoc == -1)
	{
		std::cout << "Failed to find alpha uniform\n";
		return;
	}
	glUniform1f(alphaLoc, alpha);
}

void Shader::SetLightAmount(int amount) const
{
	if(lightAmountLoc == -1)
	{
		std::cout << "Failed to find lightAmount uniform\n";
		return;
	}
	glUniform1i(lightAmountLoc, amount);
}

void Shader::SetLightPositions(const std::vector<Vector3>& positions) const
{
	if(lightPositionsLoc == -1)
	{
		std::cout << "Failed to find lightPositions uniform\n";
		return;
	}
	for(int i = 0; i < positions.size(); ++i)
	{
		std::string name = "lightPositions[" + std::to_string(i) + "]";
		GLint loc = glGetUniformLocation(ID, name.c_str());
		if(loc != -1)
			glUniform3fv(loc, 1, positions[i].data());
	}
	SetLightAmount((int)positions.size());
}

void Shader::SetLightColors(const std::vector<Vector3>& colors) const
{
	if(lightColorsLoc == -1)
	{
		std::cout << "Failed to find lightColors uniform\n";
		return;
	}
	for(int i = 0; i < colors.size(); ++i)
	{
		std::string name = "lightColors[" + std::to_string(i) + "]";
		GLint loc = glGetUniformLocation(ID, name.c_str());
		if(loc != -1)
			glUniform3fv(loc, 1, colors[i].data());
	}
	SetLightAmount((int)colors.size());
}

void Shader::SetLightUniforms(int amount,
							  const std::vector<Vector3>& colors,
							  const std::vector<Vector3>& positions) const
{
	SetLightAmount(amount);
	SetLightColors(colors);
	SetLightPositions(positions);
}

//for now all are bound to texture unit 0
void Shader::ActivateTexture(GLuint textureID, GLuint unit) const
{
	if(textureSamplerLoc == -1)
	{
		std::cout << "Failed to find texture uniform: " << textureSamplerLoc << "\n";
		return;
	}

	//glActiveTexture(GL_TEXTURE0 + unit); // select texture unit
	//glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(textureSamplerLoc, unit);

	TextureManager::BindTexture(textureID, unit);
}
