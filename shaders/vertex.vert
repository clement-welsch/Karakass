#version 460 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texCoords;

uniform mat4 u_mvp;
out vec2 v_texCoords;

void main()
{
	gl_Position = pos * u_mvp;
	v_texCoords = texCoords;
}