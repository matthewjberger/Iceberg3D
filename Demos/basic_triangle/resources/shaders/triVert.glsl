#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;

out vec3 f_color;

void main()
{
   gl_Position = vec4(v_position, 1.0f);
   f_color = v_color;
}