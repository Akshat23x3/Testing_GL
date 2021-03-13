#include "Shader_Object.h"
#include "ARKEngine.h"
#include "Transformations_Projections.h"
#include "Light.h"
#include "MeshComponent.h"
#include "CubeMapping.h"
#include <vector>


class Application : public Engine::GL_GRAPHICS
{
    std::vector<MeshComponent*> meshcomps;
    std::vector<PointLight> point_lights;
    DirectionalLight* Global_lighting = 0;
    SpotLight* spot_light = 0;
    LIGHT_SHADER* light_shader = 0;
    CubeMapping* skybox = 0;
    std::vector<Shader_Object*> shaders;
    //Primitive_Models* model_p = 0;
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

    
   // model_p = new Primitive_Models();
    //shaders.push_back(model_p->Load_Plane("Data/Textures/floor.png"));
    meshcomps.push_back(new MeshComponent());
    shaders.push_back(meshcomps[0]->Load_Model("Data/models/nanosuit/", "nanosuit.obj"));
    meshcomps.push_back(new MeshComponent());
    shaders.push_back(meshcomps[1]->Load_Model("Data/models/tree_rocks/", "tree_X14_+X1_Rock_Pack.obj"));


    //Light
    light_shader = CreateObjectComponent<LIGHT_SHADER>();
    light_shader->Initiate_Shader();
    Global_lighting = CreateObjectComponent<DirectionalLight>();
    Global_lighting->power = 0.2f;
    for (int i = 0; i < 2; i++)
    {
        point_lights.push_back(PointLight());
        point_lights[i].power = 5.0f;
    }
    point_lights[0].SetPosition(glm::vec3(5.0f, 2.0f, 0.0f));
    point_lights[1].SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));
    spot_light = new SpotLight();
    spot_light->SetPosition(point_lights[1].GetPosition());

    //skybox = new CubeMapping("Night_Sky.png");
}


void Application::run()
{
    EngineCamera->ProcessMovement(deltaTime, GetWindow());
    Global_lighting->power = 2.0f;
    glm::vec3 position = point_lights[0].GetPosition();
    position.x -= 0.5f * deltaTime;
    point_lights[0].SetPosition(position);
    position = point_lights[1].GetPosition();
    position.z -= 0.5f * deltaTime;
    point_lights[1].SetPosition(position);
    spot_light->SetPosition(point_lights[1].GetPosition());

    //skybox->Render(meshcomp);


    //meshcomp->Set_Rotation(glm::vec3(0.0f, 90.0f, 0.0f));
    //meshcomp->bPossesPlayer = true;
    //meshcomps[0]->Set_WorldScale(glm::vec3(0.1f));
    //meshcomps[0]->Set_WorldPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    for (auto& meshcomp : meshcomps)
    {
        meshcomp->Set_WorldScale(glm::vec3(0.1f));
        meshcomp->Set_WorldPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        meshcomp->Draw();
    }

    //model_p->Set_WorldRotation(glm::vec3(90.0f, 0.0f, 0.0f));
    //model_p->Set_WorldPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    //model_p->Draw();

    light_shader->Use(*Global_lighting, point_lights, *spot_light, shaders);
}

Application::~Application()
{
    //delete meshcomps;
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

void SetCursorEnterCallBack(GLFWwindow* window, int entered)
{
    if (entered == 1)
    {
        bCursorInWindow = true;
        //std::cout << "Cursor has Entered The Window;" << std::endl;
    }

    if(entered == 0)
    {
        bCursorInWindow = false;
        //std::cout << "Cursor has Left The Window;" << std::endl;
    }
}

void Application::initiateInput()
{
    glfwSetCursorEnterCallback(this->GetWindow(), SetCursorEnterCallBack);
    glfwSetKeyCallback(this->GetWindow(), KeyCallback);
    glfwSetCursorPosCallback(this->GetWindow(), MouseCallback);
    glfwSetScrollCallback(this->GetWindow(), ScrollCallback);
}


int main()
{
	Application* app = new Application(WINDOW_WIDTH, WINDOW_HEIGHT, 4, 6);
	delete app;
	return EXIT_SUCCESS;
}