#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 fragPosition;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
	fragPosition = vec3(u_Model * vec4(aPos, 1.0));
	gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
	Normal = vec3(u_Model * vec4(aNormal, 0.0));
}

#shader fragment
#version 330 core

in vec3 fragPosition;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColour;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;

void main()
{
	// Ambient lighting.
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	// Diffuse lighting.
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - fragPosition);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	// Specular lighting.
	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPos - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColour;

	// Resulting colour.
	vec4 Colour = texture(texture_diffuse1, TexCoords);
	vec3 frag = Colour.xyz;
	vec3 result = (ambient + diffuse) * frag;
	FragColour = vec4(result, 1.0);
}