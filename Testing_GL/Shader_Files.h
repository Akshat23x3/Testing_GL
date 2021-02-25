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

	struct Light
	{
		float strength;
		vec3 normal;
		vec3 direction;
		vec3 reflectdir;
		vec3 viewdir;
		vec3 light;
	};

	struct Light_Features
	{
		Light ambient;
		Light diffuse;
		Light specular;
	};

	struct Material
	{
		sampler2D diffuse;
		sampler2D specular;
	};

	struct LightColor
	{	
		//Point Light
		float constant;
		float linear;
		float quadratic;

		//Spot Light
		float cutOff;
		float outerCutOff;
		vec3 direction;

		float power;
		int shininess;
		
		vec3 diffuse;
		vec3 ambient;
		vec3 specular;
	};

	uniform LightColor light_color;
	uniform vec3 lightpos;
	uniform vec3 viewpos;
	uniform Material material;
	
	void main()
	{
		Light_Features light;

		//Ambient Lighting
		light.ambient.strength = light_color.power;
		light.ambient.light = light.ambient.strength * light_color.ambient * vec3(texture(material.diffuse, tex_coord));

		//Diffuse Lighting
		light.diffuse.normal = normalize(Normal);
		light.diffuse.direction = normalize(lightpos - Fragpos);
		light.diffuse.strength = max(dot(light.diffuse.normal, light.diffuse.direction), 0.0);
		light.diffuse.light = light.diffuse.strength * light_color.diffuse * vec3(texture(material.diffuse, tex_coord));

		//Specular Lighting
		light.specular.viewdir = normalize(viewpos - Fragpos);
		light.specular.reflectdir = reflect(-light.diffuse.direction, light.diffuse.normal);
		light.specular.strength = pow(max(dot(light.specular.viewdir, light.specular.reflectdir), 0.0f), light_color.shininess);
		light.specular.light = light.specular.strength * light_color.specular * vec3(texture(material.specular, tex_coord));
		
		//SpotLight
		/*float theta = dot(light.diffuse.direction, normalize(-light_color.direction));
		float epsilon = light_color.cutOff - light_color.outerCutOff;
		float intensity = clamp((theta - light_color.outerCutOff) / epsilon, 0.0f, 1.0f);
		light.diffuse.light  *= intensity;
		light.specular.light *= intensity;*/

		//Point Light
		float distance = length(lightpos - Fragpos);
		float attenuation = 1.0f / (light_color.constant + (light_color.linear * distance) + (light_color.quadratic * (distance * distance)));

		light.ambient.light *= attenuation;
		light.diffuse.light *= attenuation;
		light.specular.light *= attenuation;

		color = vec4(light.ambient.light + light.diffuse.light + light.specular.light, 1.0f);
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