#version 330 core
layout(location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_VP;

void main()
{
	TexCoords = vertex.zw;
	gl_Position = u_VP * u_Model * vec4(vertex.xy, 0.0f , 1.0f);
}
