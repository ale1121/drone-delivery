#version 330

layout(location = 0) out vec4 out_color;

in float noise_val;
in vec3 world_position;
uniform vec3 drone_position;

void main()
{
	vec4 fog_color = vec4(0.06, 0.08, 0.30, 1);
	vec4 color1 = vec4(0.5, 0.5, 1, 1);
	vec4 color2 = vec4(1, 1, 1, 1);
	vec4 color = mix(color1, color2, noise_val * 0.5);

	float dist = distance(drone_position, world_position);
	float fog_intensity = clamp(dist * dist * 0.002, 0.0, 1.0);
	out_color = mix(color, fog_color, fog_intensity);
}
