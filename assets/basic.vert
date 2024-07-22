#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormal;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(inPos, 1.0);
    vTexCoord = inTexCoord;
    vNormal = mat3(transpose(inverse(uModel))) * inNormal;
    vFragPos = vec3(uModel * vec4(inPos, 1.0));
}