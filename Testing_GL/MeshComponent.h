#include "ModelLoading.h"

class MeshComponent : public Transformations
{
	Model* model = 0;
public:
	MeshComponent()
	{
	}

	Shader_Object* Load_Model(const GLchar* model_path)
	{
		model = new Model(model_path);
		return model->GetShader();
	}

	//Shader_Object* GetShader() { return model->GetShader(); }

	void Draw()
	{
		model->Draw(this);
	}
};

class Primitive_Models : public Transformations
{
	Textures* texture = 0;
	Shader_Object* shader = 0;
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	int shininess = 128;
	glm::vec3 ambient_color = glm::vec3(0.2f);
	glm::vec3 diffuse_color = glm::vec3(0.5f);
	glm::vec3 specular_color = glm::vec3(1.0f);

public:
	Shader_Object* Load_Plane(const GLchar* texture_path)
	{
		GLfloat vertices[] =
		{
			// Positions            // Normals              // Texture Coords
			-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
			0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		};


		SHADER_SOURCE_FILES* shader_file = new SHADER_SOURCE_FILES();
		this->shader = new Shader_Object(shader_file->vertex_source_primitive, shader_file->fragment_source_primitive);
		delete shader_file;
		this->shader->compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
								 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
								
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		texture = new Textures();
		texture->Load_Texture(texture_path);

		return this->shader;
	}

	void Draw()
	{
		glBindVertexArray(this->VAO);
		glUseProgram(this->shader->get_shader_program());
		 
		//Texture_Loading
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		glUniform1i(glGetUniformLocation(this->shader->get_shader_program(), "material.diffuse"), 0);

		int light_feature_loc = glGetUniformLocation(this->shader->get_shader_program(), "light_feature.ambient");
		glUniform3fv(light_feature_loc, 1, glm::value_ptr(ambient_color));

		light_feature_loc = glGetUniformLocation(this->shader->get_shader_program(), "light_feature.diffuse");
		glUniform3fv(light_feature_loc, 1, glm::value_ptr(diffuse_color));

		light_feature_loc = glGetUniformLocation(this->shader->get_shader_program(), "light_feature.specular");
		glUniform3fv(light_feature_loc, 1, glm::value_ptr(specular_color));

		int light_shininess_loc = glGetUniformLocation(this->shader->get_shader_program(), "material.shininess");
		glUniform1i(light_shininess_loc, shininess);

		int mvp_loc = glGetUniformLocation(this->shader->get_shader_program(), "MVP");
		glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(this->Project_On_Screen()));

		int model_loc = glGetUniformLocation(this->shader->get_shader_program(), "model");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(this->Get_Model_Matrix()));

		int viewpos_loc = glGetUniformLocation(this->shader->get_shader_program(), "viewpos");
		glUniformMatrix4fv(viewpos_loc, 1, GL_FALSE, glm::value_ptr(EngineCamera->GetPosition()));

		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
};