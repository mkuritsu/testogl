#version 460 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 FragColor;

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

uniform sampler2D uTexture0;
uniform vec3 uViewPos;
uniform Light uLight;
uniform Material uMaterial;

void main()
{
    vec3 materialTexture = vec3(texture(uMaterial.diffuse, vTexCoord));

    // Ambient
    vec3 ambient = uLight.ambient * materialTexture;

    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLight.position - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLight.diffuse * diff * materialTexture;

    // Specular
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 viewDir = normalize(uViewPos - vFragPos);
        float specularAngle = max(dot(viewDir, reflectDir), 0.0);
        spec = pow(specularAngle, uMaterial.shininess);
    }
    vec3 specular = uLight.specular * spec * vec3(texture(uMaterial.specular, vTexCoord));

    vec4 light = vec4(ambient + diffuse + specular, 1.0);
    FragColor = texture(uTexture0, vTexCoord) * light;
}