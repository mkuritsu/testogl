#version 460 core

out vec4 FragColor;

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

uniform sampler2D uTexture0;
uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uViewPos;

void main()
{
    // Ambient
    float ka = 0.1;
    vec3 ambient = ka * uLightColor;

    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;

    // Specular
    int shininess = 32;
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * uLightColor;

    vec4 light = vec4(ambient + diffuse + specular, 1.0);
    FragColor = texture(uTexture0, vTexCoord) * light;
}