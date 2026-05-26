#version 460 core

uniform float u_time;
uniform vec3 u_spectrum;
in vec2 v_texcoord;

out vec4 FragColor;

void main()
{
	vec2 uv = v_texcoord;

    vec3 colorA = vec3(0.15, 0.20, 0.55);
    vec3 colorB = vec3(0.85, 0.30, 0.25);
    vec3 colorC = vec3(0.10, 0.70, 0.60);

    float wave =
        0.5 + 0.5 *
        sin(uv.x * 4.0 + u_time * 0.5);

    vec3 gradient1 = mix(colorA, colorB, uv.y);
    vec3 gradient2 = mix(gradient1, colorC, wave);

    FragColor = vec4(gradient2, 1.0);
}