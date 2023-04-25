#version 330 core
layout(location = 0) out vec4 color;

in vec3 normal_world;

void main()
{
	float d = dot( normal_world, vec3(0, 0, 1) );
	d = max(d, 0);

	color = vec4(d, d, d, 1.0);
}



