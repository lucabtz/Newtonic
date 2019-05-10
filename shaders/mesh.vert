#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 modl;

void main()
{
  vec4 vert = vec4(vertexPosition, 1.0);
  gl_Position = proj * view * modl * vert;
}
