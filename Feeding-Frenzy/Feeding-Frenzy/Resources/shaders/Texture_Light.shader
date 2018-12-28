#shader vertex
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 normalCoord;

uniform mat4 u_MVP;
out vec2 TextCoord;
out vec3 normal_worldspace;
out vec3 position_worldspace;

void main()
{
	gl_Position = u_MVP * vec4(Position, 1.0);
	TextCoord = textCoord;
	normal_worldspace = vec3(gl_Position);
	position_worldspace = normalize(vec3(u_MVP * vec4(normalCoord, 0)));
}

#shader fragment
#version 330 core

uniform sampler2D myTextureSampler;
uniform vec3 LightPosition_worldspace;
uniform vec3 EyePosition_worldspace;
uniform vec3 ambientLight;

in vec2 TextCoord;
in vec3 position_worldspace;
in vec3 normal_worldspace;

out vec4 u_color;

void main()
{
	u_color = texture(myTextureSampler, TextCoord);

	vec3 material = u_color.rgb;

	//ambient light
	vec3 Ambient = ambientLight * material;

	//diffuse light
	vec3 lightVector = normalize(LightPosition_worldspace - position_worldspace);
	float brightness = dot(lightVector, normal_worldspace);
	vec3 diffuseLight = vec3(brightness, brightness, brightness);
	diffuseLight = clamp(diffuseLight, 0, 1);
	vec3 diffuse = diffuseLight * material;

	//Specular light
	vec3 reflectedLightVector = reflect(-lightVector, normal_worldspace);
	vec3 eyeDirectionVector = normalize(EyePosition_worldspace - position_worldspace);
	float specularity = dot(reflectedLightVector, eyeDirectionVector);
	float specularExponent = 0.5;
	specularity = pow(specularity, specularExponent);
	vec3 specularLight = vec3(specularity, specularity, specularity);
	specularLight = clamp(specularLight, 0, 1);
	vec3 Specular = specularLight * material;

	vec3 finalColor = Ambient + diffuse + Specular;
	u_color = vec4(finalColor, u_color[3]);
}