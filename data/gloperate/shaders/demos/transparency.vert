
#version 140
#extension GL_ARB_explicit_attrib_location : require


uniform vec3 alphaVals;


layout (location = 0) in vec2 a_vertex;
layout (location = 1) in vec2 a_uv;
layout (location = 2) in vec3 a_color;
layout (location = 3) in int a_index;

flat out vec4 v_color;
out vec2 v_localPos;


void main()
{
    gl_Position = vec4(a_vertex, 0.0, 1.0);
    v_color = vec4(a_color, alphaVals[a_index]);
    v_localPos = a_uv;
}
