#version 330 core

in vec3 Pos_frag;
in vec3 Normal;

out vec4 color;

uniform vec3 color_object;
uniform vec3 color_light;
uniform vec3 pos_light;

void main()
{
	/* Ambient lighting */
	float ambient_strength = 0.1f;
	vec3 ambient = ambient_strength * color_light;

	/* Diffuse lighting */
	vec3 norm = normalize(Normal);
	vec3 dir_light = normalize(pos_light - Pos_frag);
	float diffuse_coeff = max(dot(norm, dir_light), 0.0);
	vec3 diffuse = diffuse_coeff * color_light;

	/* Sum */
	vec3 result = (ambient + diffuse) * color_object;
	color = vec4(result, 0.5f);
}
