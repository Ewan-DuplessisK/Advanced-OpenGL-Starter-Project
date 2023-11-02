#version 330 core
in vec4 ourColor;
out vec4 FragColor;
in vec4 position;

void main()
{
    FragColor=ourColor*position;
}