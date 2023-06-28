#version 330 core
layout(location = 0) out vec4 color;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_perspective_matrix;

in vec3 normal_world;
in vec2 v_tex_coord;

in float radial_velocity;
in float depth;
//in vec4 pos;

uniform int u_has_texture;
uniform float u_factor;
uniform sampler2D u_texture;

void main()
{
	float d = dot( normal_world, vec3(0, 0, 1) );
	d = max(d, 0);

    // TODO pass u_factor to shader
	// color = vec4(u_factor*radial_velocity, d, -depth, 1.);
	color = vec4(radial_velocity, d, -depth, 1.);

}



