#version 460 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;
in vec2 v_texCoords;

uniform sampler2D screen;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoords);
	color = texColor;
}