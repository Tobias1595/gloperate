
#version 150
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_shading_language_include : require

#include </gloperate/shaders/lighting/ssao.glsl>


const vec3 ssaoColor = vec3(0.0);
const float farZ = 10.0;


uniform sampler2D colorTexture;
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;
uniform sampler1D ssaoKernelTexture;
uniform sampler2DArray ssaoNoiseTexture;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float ssaoRadius = 0.5;

uniform int currentFrame;

uniform bool useSSAO;


in vec2 v_uv;

layout (location = 0) out vec4 fragColor;


void main()
{
    vec3 baseColor = texture(colorTexture, v_uv).rgb;

    float ssaoFactor = 1.0;

    if (useSSAO)
    {
        ssaoFactor = ssao(
            v_uv,
            depthTexture,
            normalTexture,
            ssaoNoiseTexture,
            ssaoKernelTexture,
            modelViewProjectionMatrix,
            inverse(modelViewProjectionMatrix),
            ssaoRadius,
            currentFrame
        );
    }

    fragColor = vec4(baseColor * ssaoFactor, 1.0);
}
