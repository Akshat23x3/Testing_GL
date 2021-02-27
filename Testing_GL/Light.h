#include <glm/glm.hpp>
#include <vector>

//Direction Light
class DirectionalLight
{
	glm::vec3 color = glm::vec3(1.0f);
	glm::vec3 direction = glm::vec3(-1.0f, -1.0f, -1.0f);
public:
	glm::vec3 GetColor() { return this->color; }
	glm::vec3 GetDirection() { return this->direction; }

	float power = 2.0f;
	int shininess = 32;

	void SetColor(glm::vec3 color) { this->color = color; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }
};

//Point Light
class PointLight
{
	glm::vec3 color = glm::vec3(1.0f);
	glm::vec3 direction = glm::vec3(-1.0f, -1.0f, -1.0f);
	glm::vec3 position = glm::vec3(1.0f);
public:
	float power = 2.0f;
	int shininess = 32;
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;

	glm::vec3 GetColor() { return this->color; }
	glm::vec3 GetPosition() { return this->position; }
	glm::vec3 GetDirection() { return this->direction; }

	void SetColor(glm::vec3 color) { this->color = color; }
	void SetPosition(glm::vec3 position) { this->position = position; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }
};

//Spot Light
class SpotLight
{
	glm::vec3 color = glm::vec3(1.0f);
	glm::vec3 direction = glm::vec3(-1.0f, -1.0f, -1.0f);
	glm::vec3 position = glm::vec3(1.0f);
public:

	float power = 2.0f;
	int shininess = 32;
	float CutOff = glm::cos(glm::radians(12.5f));
	float OuterCutOff = glm::cos(glm::radians(17.5f));
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;

	glm::vec3 GetColor() { return this->color; }
	glm::vec3 GetPosition() { return this->position; }
	glm::vec3 GetDirection() { return this->direction; }

	void SetColor(glm::vec3 color) { this->color = color; }
	void SetPosition(glm::vec3 position) { this->position = position; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }
};

class LIGHT_SHADER
{
protected:
	GLuint VAO = 0, VBO = 0;
	Shader_Object* shader = 0;

public:

	//Constructors
	LIGHT_SHADER(Shader_Object* shader) { this->shader = shader;}
	LIGHT_SHADER();

	//Getters and Setters
	void ChangeShader(Shader_Object* shader) { this->shader = shader; }
	Shader_Object* GetShader() { return this->shader; }

	//Execution 
	void Initiate_Light_Source();

	//Rendering
	void Use(DirectionalLight dirlight, std::vector<PointLight> pointlights, SpotLight spotlight, Shader_Object* shader, bool Render);
	void compile_directional_light(DirectionalLight light, Shader_Object* shader);
	void compile_spot_light(SpotLight light, Shader_Object* shader);
	void compile_point_light(std::vector<PointLight> lights, Shader_Object* shader);

	~LIGHT_SHADER();
};

LIGHT_SHADER::LIGHT_SHADER()
{
	SHADER_SOURCE_FILES* shader_file = CreateObjectComponent<SHADER_SOURCE_FILES>();
	shader = new Shader_Object(shader_file->lamp_vs, shader_file->lamp_fs);
	shader->compile_shaders();
}

void LIGHT_SHADER::Initiate_Light_Source()
{
	const GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f, 
	0.5f,  0.5f, -0.5f, 
	0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f, 
	0.5f,  0.5f,  0.5f, 
	0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f, 
	0.5f,  0.5f, -0.5f, 
	0.5f, -0.5f, -0.5f, 
	0.5f, -0.5f, -0.5f, 
	0.5f, -0.5f,  0.5f, 
	0.5f,  0.5f,  0.5f, 

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f, 
	0.5f, -0.5f,  0.5f, 
	0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f, 
	0.5f,  0.5f,  0.5f, 
	0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	};

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//Buffers
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void LIGHT_SHADER::compile_directional_light(DirectionalLight light, Shader_Object* shader)
{
	int light_power_loc = glGetUniformLocation(shader->get_shader_program(), "directional_light.power");
	glUniform1f(light_power_loc, light.power);

	int light_shininess_loc = glGetUniformLocation(shader->get_shader_program(), "directional_light.shininess");
	glUniform1i(light_shininess_loc, light.shininess);

	int light_direction_loc = glGetUniformLocation(shader->get_shader_program(), "directional_light.direction");
	glUniform3fv(light_direction_loc, 1, glm::value_ptr(light.GetDirection()));
}

void LIGHT_SHADER::compile_spot_light(SpotLight light, Shader_Object* shader)
{
	int floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.power");
	glUniform1f(floaters, light.power);

	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.shininess");
	glUniform1i(floaters, light.shininess);

	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.constant");
	glUniform1f(floaters, light.constant);

	light.SetDirection(EngineCamera->GetForwardVector());
	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.direction");
	glUniform3fv(floaters, 1, glm::value_ptr(light.GetDirection()));

	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.linear");
	glUniform1f(floaters, light.linear);

	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.quadratic");
	glUniform1f(floaters, light.quadratic);

	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.cutoff");
	glUniform1f(floaters, light.CutOff);

	floaters = glGetUniformLocation(shader->get_shader_program(), "spot_light.outerCutOff");
	glUniform1f(floaters, light.OuterCutOff);
}

void LIGHT_SHADER::compile_point_light(std::vector<PointLight> lights, Shader_Object* shader)
{
	glUniform1i(glGetUniformLocation(shader->get_shader_program(), "lights"), lights.size());
	for (int i = 0; i < lights.size(); i++)
	{
		std::string str = "point_light[";

		std::string result = str + std::to_string(i).c_str() + "].power";
		int floaters = glGetUniformLocation(shader->get_shader_program(), result.c_str());
		glUniform1f(floaters, lights[i].power);

		result = str + std::to_string(i).c_str() + "].shininess";
		floaters = glGetUniformLocation(shader->get_shader_program(), result.c_str());
		glUniform1i(floaters, lights[i].shininess);

		result = str + std::to_string(i).c_str() + "].constant";
		floaters = glGetUniformLocation(shader->get_shader_program(), result.c_str());
		glUniform1f(floaters, lights[i].constant);

		result = str + std::to_string(i).c_str() + "].linear";
		floaters = glGetUniformLocation(shader->get_shader_program(), result.c_str());
		glUniform1f(floaters, lights[i].linear);

		result = str + std::to_string(i).c_str() + "].quadratic";
		floaters = glGetUniformLocation(shader->get_shader_program(), result.c_str());
		glUniform1f(floaters, lights[i].quadratic);

		result = str + std::to_string(i).c_str() + "].position";
		floaters = glGetUniformLocation(shader->get_shader_program(), result.c_str());
		glUniform3fv(floaters, 1, glm::value_ptr(lights[i].GetPosition()));
	}
}

void LIGHT_SHADER::Use(DirectionalLight dirlight, std::vector<PointLight> pointlights, SpotLight spotlight, Shader_Object* shader, bool Render = true)
{
	compile_directional_light(dirlight, shader);
	compile_spot_light(spotlight, shader);
	compile_point_light(pointlights, shader);

	glBindVertexArray(0);

	if (!Render)
		return;

	Transformations* transform = new Transformations();

	glBindVertexArray(this->VAO);
	glUseProgram(this->shader->get_shader_program());

	for (int i = 0; i < pointlights.size(); i++)
	{
		transform->Set_Position(pointlights[i].GetPosition());
		transform->Set_Rotation(glm::vec3(0.0f));
		transform->Set_Scale(glm::vec3(0.2f));

		int transform_loc = glGetUniformLocation(this->shader->get_shader_program(), "MVP");
		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform->Project_On_Screen()));

		int color_loc = glGetUniformLocation(this->shader->get_shader_program(), "light_color");
		glUniform3fv(color_loc, 1, glm::value_ptr(pointlights[i].GetColor()));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}

LIGHT_SHADER::~LIGHT_SHADER()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader->get_shader_program());
}