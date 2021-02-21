#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

class SHADER_SOURCE_FILES
{
public:
	const char* vertex_source = R"(
	#version 460 core

	layout(location = 0) in vec3 position;
	layout(location = 2) in vec3 texcoord;

	out vec2 tex_coord;

	uniform mat4 MVP;
		
	void main()
	{
		gl_Position = MVP * vec4(position, 1.0);
		tex_coord = vec2(texcoord.x, 1.0 - texcoord.y);
	}
	)";

	const char* fragment_source = R"(

	#version 460 core
	
	in vec2 tex_coord;
	out vec4 color;

	//uniform vec3 light_color;

	uniform sampler2D Texture;
	
	void main()
	{
		color = texture(Texture, tex_coord);
	}
	)";

	const GLchar* lamp_vs = R"(

	#version 460 core

	layout(location = 0) in vec3 position;

	uniform mat4 MVP;
		
	void main()
	{
		gl_Position = MVP * vec4(position, 1.0f);
	}
	)";

	const GLchar* lamp_fs = R"(

	#version 460 core

    uniform vec3 light_color;
	out vec4 color;
	
	void main()
	{
		color = vec4(light_color, 1.0f);
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