#version 330 core
in vec3 pos;
uniform mat4 mv_matrix;
uniform mat4 projection;

out VS_OUT{
vec4 color;
vec2 tc;
} vs_out;

void main()
{
    gl_Position =  projection * mv_matrix * vec4(pos, 1.0);
    vs_out.color = vec4((pos*2.0f)+1.0f, 1.0);
    
    int face = gl_VertexID/6;

    if(face ==0 ||face == 2) {
        vs_out.tc = (pos.xy * 2.0f) + vec2(0.5f, 0.5f);
    }
    else if (face ==1 ||face == 3) {
        vs_out.tc = (pos.yz * 2.0f) + vec2(0.5f, 0.5f);
    }
    else if (face ==4 ||face == 5) {
        vs_out.tc = (pos.xz * 2.0f) + vec2(0.5f, 0.5f);
    }
}