#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 light_position;
uniform float material_kd;

out vec3 frag_color;
out vec3 world_position;

void main()
{
    vec3 light_color = vec3(1, 1, 0.2);

    world_position = (Model * vec4(v_position, 1)).xyz;

    vec3 L = normalize(light_position - world_position);

    float ambient_light = 0.5;
    float diffuse_light = material_kd * max(dot(L, L), 0);

    float attenuation = 1.0 / distance(light_position, world_position);
    vec3 light = light_color * (ambient_light + attenuation * diffuse_light);

    frag_color = v_color * light;
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
