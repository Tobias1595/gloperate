
#version 140
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_shading_language_include : require

#define LIGHT_PROCESSING_PHONG
#include </gloperate/shaders/lighting/lightprocessing.glsl>


uniform samplerBuffer colorTypeData;
uniform samplerBuffer positionData;
uniform samplerBuffer attenuationData;

uniform vec3 eye;
uniform float glossiness;


in vec3 v_worldPosition;
flat in vec3 v_normal;

layout (location = 0) out vec4 fragColor;


void main()
{
    vec3 color = lightIntensity(
        v_worldPosition,
        vec3(1.0),
        vec3(0.5),
        v_normal,
        glossiness,
        eye,
        colorTypeData,
        positionData,
        attenuationData);

    fragColor = vec4(color, 1.0);
}
