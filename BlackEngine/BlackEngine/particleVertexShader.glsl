#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec2 in_uv;
layout(location = 4) in mat4 model;

uniform mat4 view;
uniform mat4 projection;


out vec4 color;
out vec3 normal;
out vec3 position;
out vec2 uv;

void main(void)
{
  uv = in_uv;
  mat3 normalMatrix = mat3(model);
  normal = normalize(normalMatrix * in_normal);
  color = in_color;


  gl_Position = projection * view * model * vec4(in_position, 1);
  position = model[3].xyz;
}
