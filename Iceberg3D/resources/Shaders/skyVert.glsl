#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;


void main()
{
    vec4 finalPos = projection * view * vec4(position, 1.0f);
    gl_Position = finalPos.xyww;
    TexCoords = position;
}  