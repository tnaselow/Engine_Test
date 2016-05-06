#version 330 core

layout(location = 0) in vec3 position;

out vec3 fragPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * transform * vec4(position.xyz, 1.0);
	fragPos = vec3(transform * vec4(position, 1.0f));
}