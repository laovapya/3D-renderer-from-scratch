#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 localMatrix;

out vec3 Normal;
out vec3 VertexWorld;

void main()
{
    Normal = normalize(mat3(localMatrix) * aNormal); //multiply by rotation matrix
 

    VertexWorld = vec3(localMatrix * vec4(aPos, 1.0));
    gl_Position = projection * viewMatrix * localMatrix * vec4(aPos, 1.0);
}