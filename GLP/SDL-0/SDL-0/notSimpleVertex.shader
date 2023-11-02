#version 330 core
in vec3 pos;
in vec3 color;
out vec4 ourColor;
uniform vec3 offset;
out vec4 position;

void main()
{
    ourColor =vec4(color,1.0);
    gl_Position = vec4(-pos/offset, 1.5);
    position = gl_Position;
}