#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "system.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Engine
{
	//IMGUI WINDOW
	class ImGui_EventWindow
	{
	public:
		ImGui_EventWindow(GLFWwindow* window)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 460");
			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
		}

		void Frame_Rendering()
		{
			// feed inputs to dear imgui, start new frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void Render()
		{
			// Render GUI
			ImGui::Begin("Scene");
			ImGui::Button("Hello!");
			ImGui::End();

			// Render dear imgui into screen
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void Shutdown()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	};



	//GRAPHICS CLASS

	class GL_GRAPHICS
	{
		GLFWwindow* window = 0;
		ImGui_EventWindow* imguiwindow = 0;
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

		glewExperimental = GL_TRUE;

		if (GLEW_OK != glewInit())
		{
			std::cout << "Failed to initialize GLEW" << std::endl; return EXIT_FAILURE;
		}

		glViewport(0, 0, screenWidth, screenHeight);

		this->Begin();

		GLfloat lastframe = 0.0f;

		imguiwindow = new ImGui_EventWindow(window);

		this->initiateInput();

		while (!glfwWindowShouldClose(window))
		{
			if (glfwGetMouseButton(GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && bCursorInWindow || bCursorInWindow && bActivateInCursor)
			{
				bActivateInCursor = true;
				glfwSetInputMode(GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				bActivateInCursor = false;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}

			//DeltaTime
			GLfloat currentframe = (GLfloat)glfwGetTime();
			deltaTime = currentframe - lastframe;
			lastframe = currentframe;
			/// 

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//ImGui Frame Rendering
			imguiwindow->Frame_Rendering();

			//Rendering
			this->run();

			//ImGui Render
			imguiwindow->Render();

			//Setting Front and Back Buffers
			glfwSwapBuffers(window);

			//Poll and Process Events
			glfwPollEvents();
		}


		imguiwindow->Shutdown();
		glfwTerminate();


	}
}
