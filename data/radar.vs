#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_perspective_matrix;

out vec3 normal_world;
out vec2 v_tex_coord;

out float radial_velocity;
out float depth;
//out vec4 pos;


void main()
{
	normal_world = vec3(u_view_matrix * u_model_matrix * vec4(normal, 0.0) );
	normal_world = normalize(normal_world);

	v_tex_coord = tex_coord;

	gl_Position =  u_perspective_matrix * u_view_matrix * u_model_matrix * position;
	depth = (u_view_matrix * u_model_matrix * position).z;
	//pos = position;


	// radial velocity:
	vec3 spin = vec3(0., 0., 1.);

	vec3 velocity = cross(spin, vec3(position));
	velocity = vec3(u_view_matrix * u_model_matrix * vec4(velocity, 0.));
	radial_velocity = -velocity.z;
}


