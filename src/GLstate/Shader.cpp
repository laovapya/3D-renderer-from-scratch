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

	viewMatrixLoc = glGetUniformLocation(ID, "viewMatrix");
	
	localMatrixLoc = glGetUniformLocation(ID, "localMatrix");
	
	colorLoc = glGetUniformLocation(ID, "color");

	
	alphaLoc = glGetUniformLocation(ID, "alpha");
	
	projectionLoc = glGetUniformLocation(ID, "projection");
	
	lightColorLoc = glGetUniformLocation(ID, "lightColor");
	
	lightPosLoc = glGetUniformLocation(ID, "lightPosition");
	

}

// Activates the Shader Program
void Shader::Activate() const
{
	glUseProgram(ID);
}

// Deletes the Shader Program
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
void Shader::SetLightColor(glm::vec3 color) const {
	if (lightColorLoc == -1) {
		std::cout << "Failed to find light color uniform" << std::endl;
		return;
	}
	glUniform3f(lightColorLoc, color.x, color.y, color.z);
}
void Shader::SetLightPosition(glm::vec3 position) const {
	if (lightPosLoc == -1) {
		std::cout << "Failed to find light position uniform" << std::endl;
		return;
	}
	glUniform3f(lightPosLoc, position.x, position.y, position.z);
}
