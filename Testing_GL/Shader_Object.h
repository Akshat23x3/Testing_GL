#include "Shader_Files.h"
#include <iostream>

class Shader_Object : protected SHADER_SOURCE_FILES
{
	GLuint vertex_shader = 0, fragment_shader = 0;
	GLuint shader_program = 0;

	void Build_vertex_shader();
	void Build_fragment_shader();

public:
	void compile_shaders();
	GLuint get_shader_program() { return this->shader_program; }
};

void Shader_Object::Build_fragment_shader()
{
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source/*load_shader("SHADER.fs")*/, NULL);
	glCompileShader(fragment_shader);


	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, 0, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader_Object::Build_vertex_shader()
{
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source/*load_shader("SHADER.vs")*/, NULL);
	glCompileShader(vertex_shader);


	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, 0, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

	}
}

void Shader_Object::compile_shaders()
{
	//Executing Shader
	Build_vertex_shader();
	Build_fragment_shader();

	this->shader_program = glCreateProgram();

	//Attaching and Linking Shaders and programs
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	int success; GLchar infoLog[512];

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->shader_program, 512, 0, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}