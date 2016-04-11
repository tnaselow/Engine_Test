#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float blendFactor;

uniform vec3 objColor;

void main()
{
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
	color = lightColor * vec4(objColor, 1.0);
}