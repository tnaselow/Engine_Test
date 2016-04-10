#include "Shader.h"

#define BUFFER_SIZE 512


void Shader::Use() const
{
	glUseProgram(this->Program);
}


Shader::Shader(const GLchar* vertPath, const GLchar* fragPath)
{
	std::ifstream vertFile;
	std::ifstream fragFile;
	std::string vertCode, fragCode;

	try
	{
		vertFile.open(vertPath);
		fragFile.open(fragPath);
		std::stringstream vertStream, fragStream;

		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();

		vertCode = vertStream.str();
		fragCode = fragStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Could not open shader files " << std::endl;
	}

	CompileShaders(vertCode.c_str(), fragCode.c_str());
}

int Shader::CompileShaders(const char* vertCode, const char* fragCode)
{
	GLuint vertId, fragID;
	int success;
	char infoLog[BUFFER_SIZE];

	vertId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertId, 1, &vertCode, NULL);
	glCompileShader(vertId);

	glGetShaderiv(vertId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertId, BUFFER_SIZE, NULL, infoLog);
		std::cout << "Could not COMPILE VERTEX SHADER: " << infoLog << std::endl;
		return 0;
	}

	fragID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragID, 1, &fragCode, NULL);
	glCompileShader(fragID);

	glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragID, BUFFER_SIZE, NULL, infoLog);
		std::cout << "Could not COMPILE FRAGMENT SHADER: " << infoLog << std::endl;
		return 0;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertId);
	glAttachShader(this->Program, fragID);
	glLinkProgram(this->Program);

	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->Program, BUFFER_SIZE, NULL, infoLog);
		std::cout << "Could not LINK SHADER: " << infoLog << std::endl;
		return 0;
	}

	glDeleteShader(vertId);
	glDeleteShader(fragID);

	return 1;
}