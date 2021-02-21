#include <glm/glm.hpp>

class Light
{
protected:
	GLuint VAO = 0, VBO = 0;
	Shader_Object* shader = 0;
	glm::vec3 color = glm::vec3(1.0f);
	glm::vec3 direction = glm::vec3(-1.0f, -1.0f, -1.0f);
	glm::vec3 position = glm::vec3(1.2f, 1.0f, 2.0f);

public:

	//Constructors
	Light(glm::vec3 color, glm::vec3 direction, glm::vec3 position);
	Light(Shader_Object* shader) { this->shader = shader;}
	Light();

	//Getters and Setters
	void SetColor(glm::vec3 color) { this->color = color; }
	void SetPosition(glm::vec3 position) { this->position = position; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }
	void ChangeShader(Shader_Object* shader) { this->shader = shader; }

	Shader_Object* GetShader() { return this->shader; }
	glm::vec3 GetColor() { return this->color; }
	glm::vec3 GetPosition() { return this->position; }
	glm::vec3 GetDirection() { return this->direction; }

	//Execution 
	void Initiate_Light_Source();

	//Rendering
	void Use();

	~Light();
};

Light::Light(glm::vec3 color, glm::vec3 direction, glm::vec3 position)
{
	this->color = color;
	this->direction = direction;
	this->position = position;

	SHADER_SOURCE_FILES* shader_file = CreateObjectComponent<SHADER_SOURCE_FILES>();
	shader = new Shader_Object(shader_file->lamp_vs, shader_file->lamp_fs);
	shader->compile_shaders();
}

Light::Light()
{
	SHADER_SOURCE_FILES* shader_file = CreateObjectComponent<SHADER_SOURCE_FILES>();
	shader = new Shader_Object(shader_file->lamp_vs, shader_file->lamp_fs);
	shader->compile_shaders();
}

void Light::Initiate_Light_Source()
{
	const GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//Buffers
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Light::Use()
{
	glUseProgram(this->shader->get_shader_program());

	Transformations* transform = CreateObjectComponent<Transformations>();
	transform->Set_Position(this->position);
	transform->Set_Rotation(glm::vec3(0.0f));
	transform->Set_Scale(glm::vec3(0.2f));

	int transform_loc = glGetUniformLocation(this->shader->get_shader_program(), "MVP");
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform->Project_On_Screen()));

	int color_loc = glGetUniformLocation(this->shader->get_shader_program(), "light_color");
	glUniform3fv(color_loc, 1, glm::value_ptr(this->color));
	
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

Light::~Light()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader->get_shader_program());
}