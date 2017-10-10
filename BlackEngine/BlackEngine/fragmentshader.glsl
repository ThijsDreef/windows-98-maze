#version 450 core
layout(location = 0) out vec4 out_color;

vec4 diffuse = vec4(1, 1, 1, 1);
vec4 ambient= vec4(0.1, 0.1, 0.1, 0.1);
vec4 specular = vec4(1, 1, 1, 1);
float shininess = 0.1f;
int texCount = 1;

float power = 10;
in vec4 color;
in vec3 normal;
in vec3 eye;
in vec3 lightDir;
void main (void)
{
  vec4 spec = vec4(0.0);
  float mag = length(lightDir);
  vec3 n = normalize(normal);
  vec3 l = normalize(lightDir);
  vec3 e = normalize(eye);

  float intensity = max(dot(n,l), 0.0);


  //if (intensity > 0.0) {

    //vec3 h = normalize(l + e);
    //float intSpec = max(dot(h,n), 0.0);
    //spec = specular * pow(intSpec, shininess);
  //}

  out_color = max((intensity * diffuse + spec), ambient) ;
}
