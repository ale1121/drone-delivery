#version 330

layout(location = 0) in vec3 v_position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out float noise_val;
out vec3 world_position;

float random (in vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f*f*(3.0-2.0*f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{
    vec3 position = v_position;

    noise_val = noise(vec2(position.x, position.z));
    position.y = noise_val * 0.5;

    world_position = (Model * vec4(v_position, 1)).xyz;

    gl_Position = Projection * View * Model * vec4(position, 1.0);
}
