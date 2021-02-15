#include <GL/glew.h>
#include "SOIL2/SOIL2.h"

class Textures
{
	int width = 0, height = 0;
	GLuint Textire_ID = 0;
public:

	void Load_Texture(const char* texture_file_path)
	{
		glGenTextures(1, &Textire_ID);
		glBindTexture(GL_TEXTURE_2D, Textire_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* image = SOIL_load_image(texture_file_path, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Render(GLuint shader_program)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textire_ID);
		glUniform1i(glGetUniformLocation(shader_program, "Texture"), 0);
	}

	GLuint get_ID() { return Textire_ID; }
};