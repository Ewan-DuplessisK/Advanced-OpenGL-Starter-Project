#version 450 core

layout (triangles, equal_spacing, cw) in;

void main(void)
{
    // final.x = tmp.x * (1+(1-vlength)/vlength)
    vec3 tmp = (gl_TessCoord.x * gl_in[0].gl_Position +
        gl_TessCoord.y * gl_in[1].gl_Position +
        gl_TessCoord.z * gl_in[2].gl_Position);
    
    float vlength = length(tmp);
    
    tmp.x = tmp.x*(1.0f+(1.0f-vlength)/vlength);
    tmp.y = tmp.y*(1.0f+(1.0f-vlength)/vlength);
    tmp.z = tmp.z*(1.0f+(1.0f-vlength)/vlength);
    
    gl_Position = tmp;
}

