#version 430 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec2 v_texCoord;

void main()
{
  gl_Position = u_proj * u_view * u_transform * vec4(vert, 1.0);
  v_texCoord = texCoord;
}
