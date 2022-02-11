#version 330 core

	layout (location = 0) in vec4 position;

	//uniform mat4 u_model_view_projection;

	void main()
	{
		//gl_Position = u_model_view_projection * position;
		gl_Position = position;
	}
