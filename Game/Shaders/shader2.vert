#version 330 core

in vec3 a_Position;
in vec3 a_Normals;
in vec4 a_Color;

out vec3 v_Position;
out vec3 v_Normal;
out vec4 v_Color;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 normalMatrix;

void main()
{
    v_Position = a_Position;
    v_Normal = (normalMatrix * vec4( a_Normals, 1.0)).xyz;
    v_Color = a_Color;
    gl_Position = modelViewProjectionMatrix * vec4(a_Position, 1.0);

}