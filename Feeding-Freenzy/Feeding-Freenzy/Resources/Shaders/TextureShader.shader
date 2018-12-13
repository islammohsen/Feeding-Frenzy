#shader vertex
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 textCoord;

uniform mat4 u_MVP;
out vec2 TextCoord;

void main() 
{
	gl_Position = u_MVP * vec4(Position, 1.0);
	TextCoord = textCoord;
}

#shader fragment
#version 330 core

uniform sampler2D myTextureSampler;
in vec2 TextCoord;
out vec4 u_color;

void main()
{
	u_color = texture(myTextureSampler, TextCoord);
}