#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_Position[];
in vec3 v_Normal[];
in vec4 v_Color[];
in vec2 v_uv[];

out vec3 g_Position;
out vec3 g_Normal;
out vec4 g_Color;
out vec2 g_uv;

void main()
{
    for (int i = 0; i < gl_in.length(); i += 3)
    {
        // Emit the three vertices of the triangle
        for (int j = 0; j < 3; j++)
        {
            g_Position = v_Position[i + j];
            g_Normal = v_Normal[i + j];
            g_Color = v_Color[i + j];
            g_uv = v_uv[i + j];

            gl_Position = gl_in[i + j].gl_Position;
            EmitVertex();
        }
        EndPrimitive();
    }
}