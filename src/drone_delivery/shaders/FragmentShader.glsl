#version 330

in vec3 frag_color;
in vec3 world_position;

uniform vec3 drone_position;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 fog_color = vec3(0.06, 0.08, 0.30);
	float dist = distance(drone_position, world_position);
	float fog_intensity = clamp(dist * dist * 0.002, 0.0, 1.0);
	out_color = vec4(mix(frag_color, fog_color, fog_intensity), 1);
}
