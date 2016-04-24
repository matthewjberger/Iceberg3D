#version 330 core

in vec2 f_texCoord;
out vec4 color;

uniform sampler2D quadTexture;

void main()
{
    color = texture(quadTexture, f_texCoord);
}