#version 330 core

in vec3 currentPosition;
in vec3 Normal;
in vec3 color;

out vec4 FragColor;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 camPos;

vec4 directionalLight()
{
    float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    return ((diffuse + ambient) * specular) * lightColor;
}

void main()
{
    FragColor = directionalLight();
}