#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 drone_position;
uniform vec2 tree_center;
uniform float tree_height;

out vec3 frag_color;
out vec3 world_position;

void main()
{
    world_position = (Model * vec4(v_position, 1)).xyz;
    frag_color = v_color;

    vec2 drone_pos = drone_position.xz;
    float dist = distance(drone_pos, tree_center);
    float r_bend = 3;

    float bend_factor = clamp(1.0 - (dist/r_bend), 0.0, 1.0);
    float height_factor = clamp(v_position.y / tree_height, 0.0, 1.0);
    float angle = bend_factor * height_factor * 0.5;

    vec2 dir = normalize(drone_pos - tree_center);
    vec3 direction = vec3(dir.x, 0.0, dir.y);
    vec3 rotation_axis = normalize(cross(direction, vec3(0.0, 1.0, 0.0)));

    vec3 new_pos = v_position * cos(angle)
            + cross(rotation_axis, v_position) * sin(angle)
            + rotation_axis * dot(rotation_axis, v_position) * (1 - cos(angle));
    
    gl_Position = Projection * View * Model * vec4(new_pos, 1.0);
}
