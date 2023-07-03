#version 330 core
			
out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec4 v_Color;

uniform vec3 cameraPoz;

void main()
{
    vec3 ambient = vec3(0.9);
    vec3 diffuse = vec3(2, 2, 2);
    vec3 specular = vec3(0.8);
    float specPower = 32;

    vec3 lightPos = vec3(2, 3, 6);
    
    
    color = vec4(0.1,0.8,0.1, 1.0);
}
