#include <GL/glew.h>

class SHADER_SOURCE_FILES
{
protected:
	const char* vertex_source = R"(
	#version 460 core

	layout(location = 0) in vec3 position;
		
	void main()
	{
		gl_Position = vec4(position, 1.0);

	}
	)";

	const char* fragment_source = R"(

	#version 460 core
	
	out vec4 color;
	
	void main()
	{
		color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	}
)";
};