#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float blendFactor;

void main()
{
  color = mix(texture(ourTexture, uv), texture(ourTexture2, uv), blendFactor);
}