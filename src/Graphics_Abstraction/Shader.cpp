#include"shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout<<filename << " wrong shader file path"<<std::endl;
	throw(errno);
}

Shader::Shader() {
	ID = -1;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
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

	// Create Shader Program 
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	viewMatrixLoc = glGetUniformLocation(ID, "viewMatrix");
	
	localMatrixLoc = glGetUniformLocation(ID, "localMatrix");
	
	colorLoc = glGetUniformLocation(ID, "color");

	
	alphaLoc = glGetUniformLocation(ID, "alpha");
	
	projectionLoc = glGetUniformLocation(ID, "projection");

	lightAmountLoc = glGetUniformLocation(ID, "lightAmount");
	lightPositionsLoc = glGetUniformLocation(ID, "lightPositions");
	lightColorsLoc = glGetUniformLocation(ID, "lightColors");

}

void Shader::Activate() const
{
	glUseProgram(ID);
}

void Shader::Delete() const
{
	glDeleteProgram(ID);
}

void Shader::SetProjectionMatrix(glm::mat4 matrix) const {
	if (projectionLoc == -1) {
		std::cout << "Failed to find projection uniform" << std::endl;
		return;
	}
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetViewMatrix(glm::mat4 matrix) const{
	if (viewMatrixLoc == -1) {
		std::cout << "Failed to find view matrix uniform" << std::endl;
		return;
	}
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetLocalMatrix(glm::mat4 matrix) const{
	if (localMatrixLoc == -1) {
		std::cout << "Failed to find local matrix uniform" << std::endl;
		return;
	}
	glUniformMatrix4fv(localMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetRenderColor(glm::vec3 color) const {
	if (colorLoc == -1) {
		std::cout << "Failed to find border color uniform" << std::endl;
		return;
	}
	glUniform3f(colorLoc, color.x, color.y, color.z);
}

void Shader::SetAlpha(float alpha) const {
	if (alphaLoc == -1) {
		std::cout << "Failed to find alpha uniform" << std::endl;
		return;
	}
	glUniform1f(alphaLoc, alpha);
}


void Shader::SetLightAmount(int amount) const {
	if (lightAmountLoc == -1) {
		std::cout << "Failed to find light amount uniform" << std::endl;
		return;
	}
	glUniform1i(lightAmountLoc, amount);
}

void Shader::SetLightPositions(const std::vector<glm::vec3>& positions) const {
	
	if (lightPositionsLoc == -1) {
		std::cout << "Failed to find lightPositions uniform" << std::endl;
		return;
	}
	for (int i = 0; i < positions.size(); ++i) {
		std::string name = "lightPositions[" + std::to_string(i) + "]";
		GLint loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform3fv(loc, 1, glm::value_ptr(positions[i]));
	}
	SetLightAmount(positions.size());
}

void Shader::SetLightColors(const std::vector<glm::vec3>& colors) const {

	if (lightColorsLoc == -1) {
		std::cout << "Failed to find lightColors uniform" << std::endl;
		return;
	}
	for (int i = 0; i < colors.size(); ++i) {
		std::string name = "lightColors[" + std::to_string(i) + "]";
		GLint loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform3fv(loc, 1, glm::value_ptr(colors[i]));
	}
	SetLightAmount(colors.size());
}
void Shader::SetLightUniforms(int amount, const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& positions) const {
	SetLightAmount(amount);
	SetLightColors(colors);
	SetLightPositions(positions);
}