#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 Normal;
out vec3 VertexWorld;
out vec2 texCoord;

void main()
{
    Normal = normalize(mat3(modelMatrix) * aNormal); //multiply by rotation matrix
 

    VertexWorld = vec3(modelMatrix * vec4(aPos, 1.0));
    gl_Position = projection * viewMatrix * modelMatrix * vec4(aPos, 1.0);

    texCoord = aTexCoord;
}