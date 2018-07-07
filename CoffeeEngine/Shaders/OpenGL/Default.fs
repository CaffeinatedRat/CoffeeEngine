#version 330 core

//Input variables
in vec4 vertexColor;
in vec2 textureCoord;

//Output variables
out vec4 FragColor; 

//Uniforms
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, textureCoord) * vertexColor;
}