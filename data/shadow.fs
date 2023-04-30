#version 330 core
layout(location = 0) out vec4 color;

in vec3 normal_eye;
in vec3 light_position_eye;
in vec3 vertex_position_eye;
in vec4 vertex_position_light;

uniform sampler2D u_depth_map;

float evaluate_shadow(vec4 vertex_position_light)
{
    float epsilon = 0.001;

    float shadow = texture(u_depth_map, vertex_position_light.xy).r;
    if (shadow + epsilon < vertex_position_light.z)  // jeżeli shadow jest dalej niż vertex_pos
        return 0.;
    return 1.;
}

void main()
{
    // shadow stuff
    vec4 vps = vertex_position_light;
    vps.xyz /= vertex_position_light.w;
    vps.xyz += 1.0;
    vps.xyz *= 0.5;
    float shadow_factor = evaluate_shadow(vps);

    vec3 light_direction = normalize(light_position_eye - vertex_position_eye);

    float d = dot(normal_eye, light_direction);
    d = max(d, 0);
	d = d * shadow_factor;

    color = vec4(d, d, d, 1.0);
}
