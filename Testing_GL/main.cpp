#include "Shader_Object.h"
#include "My_GL.h"
#include "Transformations_Projections.h"
#include "Textures.h"
#include "Light.h"



/*GLfloat vertices[] =
{
	//Position			color               Texture Coordinates
	0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,	1.0f, 1.0f, //Top Right
	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //Bottom Left
	-0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f
};*/

glm::vec3 cubePositions[] =
{
    glm::vec3(0.0f, 0.0f, -3.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

struct Last_MousePos
{
    GLfloat x = WINDOW_WIDTH / 2.0;
    GLfloat y = WINDOW_HEIGHT / 2.0;
}lastMPOS;

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

class Application : public GL_GRAPHICS
{
	Shader_Object* shader = 0;
	Textures* texture = 0;
	Transformations* transform = 0;
    Light* light = 0; 

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
    void initiateInput();
    //void UpdateInput();
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

    //Shader_Files Initiating
    SHADER_SOURCE_FILES* shader_file = CreateObjectComponent<SHADER_SOURCE_FILES>();

	// Objects
	shader = new Shader_Object(shader_file->vertex_source, shader_file->fragment_source);
	texture = CreateObjectComponent<Textures>();
	transform = CreateObjectComponent<Transformations>();
    light = CreateObjectComponent<Light>();

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

    //Light
    light->Initiate_Light_Source(vertices);

	texture->Load_Texture("Data/Textures/container.png");
}

void Application::run()
{
    EngineCamera->ProcessMovement(deltaTime);

    light->Use(transform);

    //Texture Rendering
    texture->Render(shader->get_shader_program());
    
    glUseProgram(shader->get_shader_program());

    glBindVertexArray(VAO);
    for (int i = 0; i < 10; i++)
    {
        transform->Set_Position(cubePositions[i]);
        glm::vec3 Rotation_angle(20.0f * i);
        transform->Set_Rotation(Rotation_angle);

        int transform_loc = glGetUniformLocation(shader->get_shader_program(), "MVP");
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform->Project_On_Screen()));
       
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    glBindVertexArray(0);
}

Application::~Application()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader->get_shader_program());

    delete shader;
    delete texture;
    delete transform;
    delete light;

}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key <= 1024)
    {
        if (GLFW_PRESS == action)
        {
            keys[key] = true;
        }
        else if (GLFW_RELEASE == action)
        {
            keys[key] = false;
        }
    }
}
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    EngineCamera->ProcessMouseScroll(yOffset);
}
void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (first_Mouse)
    {
        lastMPOS.x = xPos;
        lastMPOS.y = yPos;
        first_Mouse = false;
    }

    GLfloat xOffset = -1 * (xPos - lastMPOS.x);
    GLfloat yOffset = -1 * (lastMPOS.y - yPos);

    lastMPOS.x = xPos; lastMPOS.y = yPos;

    EngineCamera->ProcessMouseMovement(xOffset, yOffset);
}

void Application::initiateInput()
{
    glfwSetKeyCallback(this->GetWindow(), KeyCallback);
    glfwSetCursorPosCallback(this->GetWindow(), MouseCallback);
    glfwSetScrollCallback(this->GetWindow(), ScrollCallback);
    glfwSetInputMode(this->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


int main()
{
	Application* app = new Application(1280, 800, 4, 6);
	delete app;
	return EXIT_SUCCESS;
}