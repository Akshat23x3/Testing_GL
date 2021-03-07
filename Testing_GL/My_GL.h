#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "system.h"


class GL_GRAPHICS
{
	GLFWwindow* window = 0;
	
protected:
	GLint Window_Width = 1280, Window_Height = 800; int Major_Version = 4, Minor_Version = 6;
public:
	GLfloat deltaTime = 0;
	int intializeGraphics();
	virtual void Begin() = 0;
	virtual void run() = 0;
	virtual void initiateInput() = 0;
	GLFWwindow* GetWindow() { return window; }
};

int GL_GRAPHICS::intializeGraphics()
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
	window = glfwCreateWindow(Window_Width, Window_Height, "ARK GAME ENGINE", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl; return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	this->Begin();
	this->initiateInput();

	GLfloat lastframe = 0.0f;

	//Looping until window closes
	while (!glfwWindowShouldClose(window) && !glfwGetKey(this->window, GLFW_KEY_ESCAPE))
	{
		//DeltaTime
		GLfloat currentframe = (GLfloat)glfwGetTime();
		deltaTime = currentframe - lastframe;
		lastframe = currentframe;
		/// 

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rendering
		this->run();
		//Setting Front and Back Buffers
		glfwSwapBuffers(window);

		//Poll and Process Events
		glfwPollEvents();
	}

	glfwTerminate();

}