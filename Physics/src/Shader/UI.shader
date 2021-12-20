#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform bool bIs3D;

//uniform mat4 u_Model;
//uniform mat4 u_View;
//uniform mat4 u_Projection;

void main()
{
	//if (bIs3D)
	//{
	//	gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
	//}
	//else
	//{
	//	gl_Position = vec4(aPos, 1.0);
	//}
	gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec2 TexCoord;

out vec4 FragColour;

uniform sampler2D ourTexture;

void main()
{
	FragColour = texture(ourTexture, TexCoord);
}