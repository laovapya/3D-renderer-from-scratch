#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;



void main()
{
    gl_Position = projection * viewMatrix * modelMatrix  * vec4(aPos, 1.0);
}