#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform float alpha;
uniform vec3 lightPosition;
uniform vec3 lightColor;


in vec3 Normal; 
in vec3 VertexWorld; 


void main()
{
    vec3 lightDir = normalize(lightPosition - VertexWorld); 

    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = (ambient + diffuse) * color;
    FragColor = vec4(result, alpha);
}