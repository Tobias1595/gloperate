
#version 330
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_shading_language_include : require

#include </gloperate/shaders/util/random.glsl>


const vec3 baseColor = vec3(1.0, 1.0, 1.0);


uniform sampler2D transparencyKernel;

uniform int currentFrame;

uniform bool useTransparency;
uniform float transparencyAlpha;


in vec4 v_position;
in vec3 v_color;
flat in vec3 v_normal;

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec3 normal;


void main()
{
    float rand = random(v_position);

    float alpha = transparencyAlpha;
    ivec2 transpSize = textureSize(transparencyKernel, 0);
    ivec2 transpIndex = ivec2(vec2(rand, alpha) * transpSize) + ivec2(currentFrame, 0);
    bool opaque = texelFetch(transparencyKernel, transpIndex % transpSize, 0).r > 0.5;

    if (alpha == 1.0)
        opaque = true;

    if (!opaque && useTransparency)
        discard;

    fragColor = vec4(v_color, 1.0);
    normal = v_normal;
}
