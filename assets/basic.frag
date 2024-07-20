#version 460 core

out vec4 FragColor;

// in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
    FragColor = mix(texture(uTexture0, vTexCoord), texture(uTexture1, vTexCoord), 0.2);
}