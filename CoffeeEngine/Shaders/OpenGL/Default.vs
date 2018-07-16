#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexture;
  
//Output variables
out vec4 vertexColor;
out vec2 textureCoord;

//Uniforms
uniform mat4 transform;
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * world * vec4(aPos, 1.0);
    vertexColor = aColor;
	textureCoord = vec2(aTexture.x, aTexture.y);
}