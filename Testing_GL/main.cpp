#include "Shader_Object.h"
#include "My_GL.h"
#include "Transformations_Projections.h"
#include "Light.h"
#include "ModelLoading.h"
#include <vector>

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
const GLfloat vertices[] = {
    // Positions            // Normals              // Texture Coords
    -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
};

class Application : public GL_GRAPHICS
{
	Shader_Object* shader = 0;
	Transformations* transform = 0;
    std::vector<PointLight> point_lights;
    DirectionalLight* Global_lighting = 0;
    LIGHT_SHADER* light_shader = 0;
    Model* model = 0;
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

    //Shader_Files Initiatings
    SHADER_SOURCE_FILES* shader_file = CreateObjectComponent<SHADER_SOURCE_FILES>();

	// Objects
	shader = new Shader_Object(shader_file->vertex_source, shader_file->fragment_source);
	transform = CreateObjectComponent<Transformations>();

	shader->compile_shaders();

    model = new Model("Data/models/nanosuit.obj");

    //Light
    light_shader = CreateObjectComponent<LIGHT_SHADER>();
    light_shader->Initiate_Shader();
    Global_lighting = CreateObjectComponent<DirectionalLight>();
    Global_lighting->power = 0.2f;
    for (int i = 0; i < 2; i++)
    {
        point_lights.push_back(PointLight());
        if (i == 1)
            point_lights[i].SetPosition(glm::vec3(-3.0f));
    }
}


void Application::run()
{
    EngineCamera->ProcessMovement(deltaTime);
    Global_lighting->power = 5.0f;
    glm::vec3 position = point_lights[1].GetPosition();
    position.z -= 0.5f * deltaTime;
    point_lights[1].SetPosition(position);

    transform->Set_Scale(glm::vec3(0.1f));
    transform->Set_Position(glm::vec3(0.0f, -2.0f, -2.0f));

    glUseProgram(shader->get_shader_program());

    model->Draw(shader, transform);

    light_shader->Use(*Global_lighting, point_lights, SpotLight(), shader);
}

Application::~Application()
{

	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader->get_shader_program());

    delete shader;
    delete transform;
    delete light_shader;

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