#version 330 core

in vec3 normal;
in vec2 texCoords;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main(void)
{
   color = vec4(texture(texture_diffuse1, texCoords));
}
