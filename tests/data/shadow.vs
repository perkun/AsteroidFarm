#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_perspective_matrix;

uniform mat4 u_light_view_matrix;
uniform mat4 u_light_perspective_matrix;
uniform vec3 u_light_position;

out vec3 normal_eye;
out vec3 light_position_eye;
out vec3 vertex_position_eye;
out vec4 vertex_position_light;

void main()
{
    normal_eye = vec3(u_view_matrix * u_model_matrix * vec4(normal, 0.0));
    normal_eye = normalize(normal_eye);

    gl_Position = u_perspective_matrix * u_view_matrix * u_model_matrix * position;

	light_position_eye = vec3(u_view_matrix * vec4(u_light_position, 1.0) );

	vertex_position_light = u_light_perspective_matrix * u_light_view_matrix
		* u_model_matrix * position;

	vertex_position_eye = vec3(u_view_matrix * u_model_matrix * position);

}
