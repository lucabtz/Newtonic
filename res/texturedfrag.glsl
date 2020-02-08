#version 430 core

in vec2 v_texCoord;

uniform sampler2D u_texture;

out vec4 color;

void main()
{
  color = texture(u_texture, v_texCoord);
}
