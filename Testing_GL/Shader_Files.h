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
	layout(location = 1) in vec3 normal;

	out vec2 tex_coord;
	out vec3 Normal;
	out vec3 Fragpos;

	uniform mat4 MVP;
	uniform mat4 model;
		
	void main()
	{
		gl_Position = MVP * vec4(position, 1.0);
		Fragpos = vec3(model * vec4(position, 1.0f));
		Normal = mat3(transpose(inverse(model))) * normal;
		tex_coord = vec2(texcoord.x, 1.0 - texcoord.y);
	}
	)";

	const char* fragment_source = R"(

	#version 460 core
	
	in vec2 tex_coord;
	in vec3 Normal;
	in vec3 Fragpos;
	
	out vec4 color;

	struct Light_Features
	{
		float power;
		float shininess;
	};
	
	struct Light
	{
		float strength;
		vec3 normal;
		vec3 direction;
		vec3 reflectdir;
		vec3 viewdir;
		vec3 light;
	};

	struct Material
	{
		Light ambient;
		Light diffuse;
		Light specular;
	}material;

	uniform vec3 light_color;
	uniform sampler2D Texture;
	uniform vec3 lightpos;
	uniform vec3 viewpos;
	uniform Light_Features light;
	
	void main()
	{
		//Ambient Lighting
		material.ambient.strength = light.power;
		material.ambient.light = material.ambient.strength * light_color;

		//Diffuse Lighting
		material.diffuse.normal = normalize(Normal);
		material.diffuse.direction = normalize(lightpos - Fragpos);
		material.diffuse.strength = max(dot(material.diffuse.normal, material.diffuse.direction), 0.0);
		material.diffuse.light = material.diffuse.strength * light_color;

		//Specular Lighting
		material.specular.viewdir = normalize(viewpos - Fragpos);
		material.specular.reflectdir = reflect(-material.diffuse.direction, material.diffuse.normal);
		material.specular.strength = pow(max(dot(material.specular.viewdir, material.specular.reflectdir), 0.0f), 32);
		material.specular.light = light.shininess * material.specular.strength * light_color;

		color = vec4((material.ambient.light + material.diffuse.light + material.specular.light) * vec3(texture(Texture, tex_coord)), 1.0f);
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