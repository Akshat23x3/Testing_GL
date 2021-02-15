#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

class SHADER_SOURCE_FILES
{
protected:
	const char* vertex_source = R"(
	#version 460 core

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 vs_color;
	layout(location = 2) in vec3 texcoord;

	out vec3 fs_color;
	out vec2 tex_coord;
		
	void main()
	{
		fs_color = vs_color;
		tex_coord = vec2(texcoord.x, 1.0 - texcoord.y);
		gl_Position = vec4(position, 1.0);
	}
	)";

	const char* fragment_source = R"(

	#version 460 core
	
	in vec3 fs_color;
	in vec2 tex_coord;
	out vec4 color;

	uniform sampler2D Texture;
	
	void main()
	{
		color = texture(Texture, tex_coord);
	}
	)";

	/*const GLchar** load_shader(const char* shader_file_path)
	{
		std::string source_code;
		std::ifstream shader_file;
		shader_file.exceptions(std::ifstream::badbit); //To ensure if it can throw exceptions
		try
		{
			shader_file.open(shader_file_path);
			std::stringstream shader_stream;
			shader_stream << shader_file.rdbuf();
			shader_file.close();
			source_code = shader_stream.str();
		}

		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE NOT FOUND" << std::endl;
		}

		const GLchar* shader_code = source_code.c_str();

		return &shader_code;
	}*/
};