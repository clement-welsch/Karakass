#version 460 core

/*layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texCoords;

uniform mat4 u_mvp;
out vec2 uvs;

void main()
{
	gl_Position = pos * u_mvp;
	uvs = texCoords;
}*/

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 v_texcoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);

    v_texcoord = aTexCoord;
}