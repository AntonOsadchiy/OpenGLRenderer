#version 330 core

	layout (location = 0) in vec4 position;
	layout (location = 1) in vec3 vertex_normal;
	layout (location = 2) in vec2 tex_coord;

	out vec2 v_tex_coord;
	out vec3 v_vertex_normal;
	out vec3 v_fragment_pos;
	out mat3 v_normal_model;

	uniform mat4 u_model;
	uniform mat4 u_view;
	uniform mat4 u_projection;

	void main()
	{
		gl_Position = u_projection * u_view * u_model * position;
		v_tex_coord = tex_coord;
		v_vertex_normal = vertex_normal;
		v_normal_model = mat3(inverse(transpose(u_model)));

		vec4 v_fragment_pos4 = u_model * position;
		v_fragment_pos = vec3(v_fragment_pos4.x, v_fragment_pos4.y, v_fragment_pos4.z);
	}
