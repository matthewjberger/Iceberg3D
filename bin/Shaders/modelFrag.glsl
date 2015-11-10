// Example Model fragment shader

varying vec2 color;

uniform sampler2D gSampler;

void main(void)
{
    gl_FragColor = texture2D(gSampler, color.xy);
}

