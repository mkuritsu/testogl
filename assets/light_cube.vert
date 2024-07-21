#version 460 core

layout (location = 0) in vec3 inPos;

uniform mat4 uTransform;

void main()
{
    gl_Position = uTransform * vec4(inPos, 1.0);
}