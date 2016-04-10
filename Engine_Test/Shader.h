#pragma once
#define GLEW_STATIC

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GL\glew.h>

class Shader
{
	public:
		GLuint Program;

	public:
		Shader(const GLchar* vertPath, const GLchar* fragPath);

		void Use() const;

	private:
		int CompileShaders(const char* vertCode, const char* fragCode);
};