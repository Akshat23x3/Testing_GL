#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vs_color;

out vec3 fs_color;
		
void main()
{
	fs_color = vs_color;
	gl_Position = vec4(position, 1.0);
}