#version 330 core

in vec3 norms;
in vec3 fragPos;

out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float blendFactor;

uniform vec3 lightPos;

uniform vec3 objColor;
uniform vec3 lightColor;

void main()
{
	float ambientStr = 0.1f;
	vec3 ambient = ambientStr * lightColor;

	vec3 norm = normalize(norms);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	color = vec4((ambient + diffuse) * objColor, 1.0);
}