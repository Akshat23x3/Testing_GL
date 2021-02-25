#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"

class Textures
{
	int width = 0, height = 0;
	GLuint* Texture_ID = new GLuint[2];
	int textures_loaded = 0;
	glm::vec3 ambient_color = glm::vec3(0.2f);
	glm::vec3 diffuse_color = glm::vec3(0.5f);
	glm::vec3 specular_color = glm::vec3(1.0f);
public:

	void Load_Texture(const char* texture_file_path)
	{
		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		unsigned char* image = SOIL_load_image(texture_file_path, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		Texture_ID[textures_loaded] = id;
		textures_loaded++;
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Render(GLuint shader)
	{
		int light_color_loc = glGetUniformLocation(shader, "light_color.ambient");
		glUniform3fv(light_color_loc, 1, glm::value_ptr(ambient_color));

		light_color_loc = glGetUniformLocation(shader, "light_color.diffuse");
		glUniform3fv(light_color_loc, 1, glm::value_ptr(diffuse_color));

		light_color_loc = glGetUniformLocation(shader, "light_color.specular");
		glUniform3fv(light_color_loc, 1, glm::value_ptr(specular_color));

		glEnable(GL_TEXTURE_2D);
		for (int i = 0; i < textures_loaded; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, Texture_ID[i]);
			if(i == 0)
				glUniform1i(glGetUniformLocation(shader, "material.diffuse"), i);
			else
				glUniform1i(glGetUniformLocation(shader, "material.specular"), i);
		}
	}

	//GLuint* get_ID() { return Textire_ID; }
};