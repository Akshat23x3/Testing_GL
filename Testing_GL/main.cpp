#include "Shader_Object.h"
#include "My_GL.h"
#include "system.h"

GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f, //Bottom Left
	0.5f, -0.5f, 0.0f, //Bottom Right
	0.0f, 0.5f, 0.0f //
};

class Application : protected GL_GRAPHICS
{
	Shader_Object* shader = 01;
	GLuint VBO = 0, VAO = 0;
public:

	Application(GLint Window_Width, GLint Window_Height, int Major_Version, int Minor_Version)
	{
		this->Window_Height = Window_Height;
		this->Window_Width = Window_Width;
		this->Major_Version = Major_Version;
		this->Minor_Version = Minor_Version;
		this->intializeGraphics();
	}

	void Begin();
	void run();
	~Application();
};

void Application::Begin()
{
	shader = CreateObjectComponent<Shader_Object>();
	shader->compile_shaders();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); 
}

void Application::run()
{
	// Draw our first triangle
	glUseProgram(shader->get_shader_program());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

Application::~Application()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader->get_shader_program());
}

int main()
{
	Application* app = new Application(1280, 800, 4, 6);
	delete app;
	return EXIT_SUCCESS;
}