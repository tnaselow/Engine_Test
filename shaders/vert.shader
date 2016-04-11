#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 uv;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
  gl_Position = projection * view * transform * vec4(position.xyz, 1.0);
  uv = vec2(texCoords.x, -texCoords.y);
}