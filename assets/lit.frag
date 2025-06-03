#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform float alpha;

#define maxLights 32

uniform int lightAmount;
uniform vec3 lightPositions[maxLights];
uniform vec3 lightColors[maxLights];




in vec3 Normal; 
in vec3 VertexWorld; 


void main()
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < lightAmount; ++i) {
        vec3 lightDir = normalize(lightPositions[i] - VertexWorld);
        float diff = max(dot(Normal, lightDir), 0.0);
        vec3 diffuse = diff * lightColors[i];

        float ambientStrength = 0.25;
        vec3 ambient = ambientStrength * lightColors[i];

        result += (ambient + diffuse);
    }

    result *= color;
    FragColor = vec4(result, alpha);
}