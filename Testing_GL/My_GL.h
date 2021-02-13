#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class GL_GRAPHICS
{
	GLFWwindow* window = 0;
protected:
	GLint Window_Width = 1280, Window_Height = 800; int Major_Version = 4, Minor_Version = 6;
public:
	void intializeGraphics();
	virtual void Begin() = 0;
	virtual void run() = 0;
};

void GL_GRAPHICS::intializeGraphics()
{
	//Initialise the GLFW
	if (!glfwInit())
	{
		std::cout << "ERROR::GLFW::NOT_INITIALIZED";
	}

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Major_Version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Minor_Version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Creating a GLFWwindow object that we can use
	window = glfwCreateWindow(Window_Width, Window_Height, "LearnOpenGL", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	this->Begin();

	//Looping until window closes
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Rendering
		this->run();
		//Setting Front and Back Buffers
		glfwSwapBuffers(window);

		//Poll and Process Events
		glfwPollEvents();
	}

	glfwTerminate();

}