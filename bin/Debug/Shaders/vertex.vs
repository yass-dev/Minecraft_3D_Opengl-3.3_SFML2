#version 330 core

layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

void main()
{
	gl_Position.xyz = vertexColor;
 	gl_Position.w = 1.0;

 	fragmentColor = vertexColor;
}