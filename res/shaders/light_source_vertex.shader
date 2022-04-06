#version 330 core

    layout(location = 0) in vec4 position;
	layout (location = 1) in vec3 vertex_normal;
	layout (location = 2) in vec2 tex_coord;

	uniform mat4 u_model_view_projection;

    void main()
    {
        gl_Position = u_model_view_projection * position;
    }