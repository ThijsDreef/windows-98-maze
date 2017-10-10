#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec2 in_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;


out vec3 normal;
out vec4 color;
out vec3 eye;
out vec3 lightDir;
void main()
{
  normal = (view * model * vec4(in_normal, 0)).xyz;
  lightDir = (-view * model * vec4(0, 0, 0, 1)).xyz - (view * model * vec4(in_position, 1)).xyz;
  eye = view[3].xyz;


  //just to draw
  gl_Position = projection * view * model * vec4(in_position, 1);
}
