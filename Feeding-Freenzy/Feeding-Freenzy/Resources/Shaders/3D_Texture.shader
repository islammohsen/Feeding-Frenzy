#shader vertex
#version 330 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 color;

out vec4 o_color;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * Position;
	o_color = color;
};

#shader fragment
#version 330 core

out vec4 color;
in vec4 o_color;

void main()
{
	color = o_color;
};