#version 450 core

layout(triangles, fractional_even_spacing, cw) in;
in TESC_OUT{
    vec4 color;
    vec2 tc;

} tese_in[];
out TESE_OUT{
    vec4 color;
    vec2 tc;

} tese_out;
void main(void)
{
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
    gl_TessCoord.y * gl_in[1].gl_Position +
    gl_TessCoord.z * gl_in[2].gl_Position);
    tese_out.color = mix(tese_in[0].color, tese_in[1].color, gl_TessCoord.x);;
    tese_out.tc = gl_TessCoord.xy
    ;
}