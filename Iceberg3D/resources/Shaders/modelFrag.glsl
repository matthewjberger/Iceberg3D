// Example Model fragment shader

varying vec2 texCoords;

uniform sampler2D texture_diffuse1;

void main(void)
{
    gl_FragColor = texture2D(texture_diffuse1, texCoords);
}

