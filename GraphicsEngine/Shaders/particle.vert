// VERTEX SHADER
#version 410

in vec4 Position;
in vec4 Colour;

out vec4 vColour;

uniform mat4 ProjectionViewModel;

void main() 
{
	Colour = Colour;
	gl_Position = ProjectionViewModel * Position;
}