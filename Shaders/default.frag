#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform float alpha;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{

	  float ambientStrength = 1.0f;
      vec3 ambient = ambientStrength * lightColor;

      

      vec3 result = ambient * objectColor;
      FragColor = vec4(result, alpha);
}

