#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_perspective_matrix;

out vec3 normal_world;

void main()
{
	normal_world = vec3(u_view_matrix * u_model_matrix * vec4(normal, 0.0) );
	normal_world = normalize(normal_world);

	gl_Position = u_perspective_matrix * u_view_matrix * u_model_matrix * vec4(position, 1.0);
	// gl_Position = u_perspective_matrix * u_view_matrix * u_model_matrix * position;
}


