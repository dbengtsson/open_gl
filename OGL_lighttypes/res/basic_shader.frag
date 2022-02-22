#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient, diffuse, specular;
};

#define POINT_LIGHT_COUNT 4

uniform vec3 viewPosition;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINT_LIGHT_COUNT];

vec3 calcDirectionalLight(DirectionalLight light, vec3 normalDirection, vec3 viewDirection);
vec3 calcPointLight(PointLight light, vec3 normalDirection, vec3 viewDirection, vec3 fragmentPosition);
vec3 calcSpotLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

void main()
{
    vec3 normalDirection = normalize(Normal);
    vec3 viewDirection = normalize(viewPosition - FragPos);
    vec3 result = calcDirectionalLight(directionalLight, normalDirection, viewDirection);

    for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
        result += calcPointLight(pointLights[i], normalDirection, viewDirection, FragPos);
    }

    FragColor = vec4(result, 1.0);
} 

vec3 calcDirectionalLight(DirectionalLight light, vec3 normalDirection, vec3 viewDirection) {
    vec3 ambient = light.ambient * texture(material.diffuseMap, TexCoords).rgb;
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normalDirection, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuseMap, TexCoords).rgb;

    vec3 reflectDir = reflect(-lightDir, normalDirection);  
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specularMap, TexCoords).rgb;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normalDirection, vec3 viewDirection, vec3 fragmentPosition) {
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    vec3 ambient = light.ambient * texture(material.diffuseMap, TexCoords).rgb;
    vec3 lightDir = normalize(light.position - fragmentPosition);

    float diff = max(dot(normalDirection, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuseMap, TexCoords).rgb;

    vec3 reflectDir = reflect(-lightDir, normalDirection);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specularMap, TexCoords).rgb;

    return (ambient + diffuse + specular) * attenuation;
}