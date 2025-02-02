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
	throw(errno);
}

Shader::Shader() {
	ID = -1;
}
// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{

	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	matrixLoc = glGetUniformLocation(ID, "matrix");
	if (matrixLoc == -1) {
		std::cout << "Failed to find matrix uniform" << std::endl;
		return;
	}
	colorLoc = glGetUniformLocation(ID, "objectColor");
	if (colorLoc == -1) {
		std::cout << "Failed to find color uniform" << std::endl;
		return;
	}
	alphaLoc = glGetUniformLocation(ID, "alpha");
	if (alphaLoc == -1) {
		std::cout << "Failed to find alpha uniform" << std::endl;
		return;
	}
	projectionLoc = glGetUniformLocation(ID, "projection");
	if (projectionLoc == -1) {
		std::cout << "Failed to find projection uniform" << std::endl;
		return;
	}
	lightColorLoc = glGetUniformLocation(ID, "lightColor");
	if (lightColorLoc == -1) {
		std::cout << "Failed to find light color" << std::endl;
		return;
	}
	lightPosLoc = glGetUniformLocation(ID, "lightPos");
	if (lightPosLoc == -1) {
		std::cout << "Failed to find light position" << std::endl;
		return;
	}

	SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::SetMatrix(glm::mat4 matrix) {
	glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetColor(glm::vec3 color) {
	glUniform3f(colorLoc, color.x, color.y, color.z);
}
void Shader::SetAlpha(float alpha) {
	glUniform1f(alphaLoc, alpha);
}
void Shader::SetProjectionMatrix(glm::mat4 matrix) {
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetLightColor(glm::vec3 color) {
	glUniform3f(lightColorLoc, color.x, color.y, color.z);
}
void Shader::SetLightPosition(glm::vec3 position) {
	glUniform3f(lightPosLoc, position.x, position.y, position.z);
}
