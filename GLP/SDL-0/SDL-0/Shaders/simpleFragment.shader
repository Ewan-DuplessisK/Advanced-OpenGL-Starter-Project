#version 330 core
in float posx;
out vec4 color;
void main()
{
    color = vec4(0.1f, 0.4f, 0.7f, pow(posx/20,3));
}