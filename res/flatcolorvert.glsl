#version 430 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform vec4 u_color;

out vec4 v_color;

void main()
{
  gl_Position = u_proj * u_view * u_transform * vec4(vert, 1.0);
  v_color = u_color;
}
