#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCord;

out vec3 normal;
out vec2 TexCord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{ 
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	normal=aNorm;
	TexCord=aTexCord;
}