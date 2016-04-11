#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;


out vec3 norms;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
  gl_Position = projection * view * transform * vec4(position.xyz, 1.0);
  norms = normals;
  fragPos = vec3(transform * vec4(position, 1.0f));
}