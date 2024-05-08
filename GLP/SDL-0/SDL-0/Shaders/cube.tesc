#version 450 core

layout(vertices = 3) out;
uniform float ratio;

in VS_OUT{
    vec4 color;
    vec2 tc;

} tesc_in[];
out TESC_OUT{
    vec4 color;
    vec2 tc;

} tesc_out[];

void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 20.0f / ratio;
        //gl_TessLevelInner[1] = 7.0;
        gl_TessLevelOuter[0] = ratio;
        gl_TessLevelOuter[1] = ratio;
        gl_TessLevelOuter[2] = ratio;
        //gl_TessLevelOuter[3] = 5.0;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tesc_out[gl_InvocationID].color = tesc_in[gl_InvocationID].color;
    tesc_out[gl_InvocationID].tc = tesc_in[gl_InvocationID].tc;
}