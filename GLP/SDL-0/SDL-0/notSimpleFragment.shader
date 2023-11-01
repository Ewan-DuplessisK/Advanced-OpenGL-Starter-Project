#version 330 core
out vec4 FragColor;
in vec3 ourColor;
out vec3 color

void main()
{
    color=ourColor;
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

#version 330 core
in vec3 ourColor;
out vec3 color

void main()
{
    color=ourColor;
}