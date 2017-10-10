#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec2 in_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 color;
out vec2 uv;

void main()
{
	uv = in_uv;
	color = vec4(1, 1, 1, 1);
	gl_Position = projection * view * model * vec4(in_position, 1);
}
