attribute vec3 position;
varying vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos =   projection * view * vec4(position, 1.0);
    gl_Position = pos.xyww;
    TexCoords = position;
}
