#include "Shader_Object.h"
#include "My_GL.h"
#include "Transformations_Projections.h"
#include "system.h"
#include "Textures.h"

/*GLfloat vertices[] =
{
	//Position			color               Texture Coordinates
	0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,	1.0f, 1.0f, //Top Right
	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //Bottom Left
	-0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f
};*/

/*
GLfloat vertices[] = {
    -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
    0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 0.0f,
    0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
    0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
    -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,

    -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
    0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
    0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
    -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 1.0f,
    -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,

    -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    -0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
    -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
    -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,

    0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
    0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
    0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,

    -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
    0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
    -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,

    -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
    0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
    0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
    -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
    -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f
};
 */

 // use with Perspective Projection
GLfloat vertices[] = {
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

class Application : protected GL_GRAPHICS
{
	Shader_Object* shader = 0;
	Textures* texture = 0;
	Transformations* transform = 0;
	GLuint VBO = 0, VAO = 0;
	//GLuint EBO = 0;
public:

	Application(GLint Window_Width, GLint Window_Height, int Major_Version, int Minor_Version)
	{
		this->Window_Height = Window_Height;
		this->Window_Width = Window_Width;
		this->Major_Version = Major_Version;
		this->Minor_Version = Minor_Version;
		this->intializeGraphics();
	}

	void set_GL_options();
	void Begin();
	void run();
	~Application();
};

void Application::set_GL_options()
{
	glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::Begin()
{
	//Setting GL_SETTINGS AND OPTIONS
	this->set_GL_options();
	shader = CreateObjectComponent<Shader_Object>();
	texture = CreateObjectComponent<Textures>();
	transform = CreateObjectComponent<Transformations>();

	shader->compile_shaders();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	//glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); 

	texture->Load_Texture("Data/Textures/container.png");
}

void Application::run()
{
    //Texture Rendering
    texture->Render(shader->get_shader_program());
    
    glUseProgram(shader->get_shader_program());

    //Transformations
    transform->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    transform->Set_Rotation(glm::vec3(45.0f, 45.0f, 45.0f));
    int transform_loc = glGetUniformLocation(shader->get_shader_program(), "MVP");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform->Project_On_Screen()));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Application::~Application()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader->get_shader_program());
}

int main()
{
	Application* app = new Application(1280, 800, 4, 6);
	delete app;
	return EXIT_SUCCESS;
}