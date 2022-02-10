#version 330 core

	layout (location = 0) in vec4 position;
	layout (location = 1) in vec2 tex_coord;
	layout (location = 2) in vec4 vertex_color;

	out vec2 v_tex_coord;
	out vec4 v_vertex_color;

	uniform mat4 u_model_view_projection;

	void main()
	{
		gl_Position = u_model_view_projection * position;
		v_tex_coord = tex_coord;
		v_vertex_color = vertex_color;
	}
