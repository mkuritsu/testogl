#version 460 core

#define NR_LIGHTS 1

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
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

uniform Material uMaterial;

uniform DirectionalLight uDirectionLights[NR_LIGHTS];
uniform PointLight uPointLights[NR_LIGHTS];
uniform SpotLight uSpotLights[NR_LIGHTS];

vec3 CalcDirectionalLight(DirectionalLight light, vec3 norm, vec3 viewDir) 
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoord));
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, vTexCoord));
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    float distance = length(light.position - vFragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoord)) * attenuation;
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoord)) * attenuation;
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, vTexCoord)) * attenuation;
    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    float distance = length(light.position - vFragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoord)) * attenuation * intensity;
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoord)) * attenuation * intensity;
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, vTexCoord)) * attenuation * intensity;
    return ambient + diffuse + specular;
}

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(uViewPos - vFragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < NR_LIGHTS; i++) {
        result += CalcDirectionalLight(uDirectionLights[i], norm, viewDir);
    }
    for (int i = 0; i < NR_LIGHTS; i++) {
        result += CalcPointLight(uPointLights[i], norm, viewDir);
    }
    for (int i = 0; i < NR_LIGHTS; i++) {
        result += CalcSpotLight(uSpotLights[i], norm, viewDir);
    }
    FragColor = vec4(result, 1.0);
}