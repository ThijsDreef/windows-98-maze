#version 450 core
layout(location = 0) out vec4 out_color;

in vec4 color;
in vec2 uv;
uniform sampler2D tex;

void main (void)
{
	out_color = texture(tex, uv);
}
