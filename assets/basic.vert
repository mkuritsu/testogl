#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 uTransform;

void main()
{
    gl_Position = uTransform * vec4(inPos, 1.0);
    vColor = inColor;
    vTexCoord = inTexCoord;
}