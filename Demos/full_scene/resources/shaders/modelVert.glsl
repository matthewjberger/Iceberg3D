#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texCoords;

out vec2 texCoords;

uniform mat4 mvpMatrix;

void main()
{
   gl_Position = mvpMatrix * vec4(v_position, 1.0);
   texCoords = v_texCoords;
}