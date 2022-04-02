#version 330 core

	in vec2 v_tex_coord;

	layout (location = 0) out vec4 color;

	uniform sampler2D u_texture_2d;

	void main()
	{
		
		color = texture(u_texture_2d, v_tex_coord);
	}