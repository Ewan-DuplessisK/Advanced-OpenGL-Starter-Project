#version 450 core
out vec4 FragColor;

in TESE_OUT{
    vec4 color;
    vec2 tc;

} frag_in;

void main(void)
{
    FragColor = frag_in.color;
}