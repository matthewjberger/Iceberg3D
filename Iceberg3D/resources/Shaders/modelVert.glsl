// Example Model vertex shader

attribute vec3 v_position;
attribute vec3 v_normal;
attribute vec2 v_texCoords;

varying vec3 normal;
varying vec2 texCoords;

uniform mat4 mvpMatrix;

void main(void)
{
   gl_Position = mvpMatrix * vec4(v_position, 1.0);
   texCoords = v_texCoords;
   normal = v_normal;
}

