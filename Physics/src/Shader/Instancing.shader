#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in mat4 InstanceMat;

out vec4 VertexColour;

uniform vec3 u_Colour;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * InstanceMat * vec4(aPos, 1.0);
	VertexColour = vec4(u_Colour, 1.0);
}

#shader fragment
#version 330 core

in vec4 VertexColour;

out vec4 fragColour;

void main()
{
	fragColour = VertexColour;
}