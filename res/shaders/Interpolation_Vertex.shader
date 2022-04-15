#version 330

layout(location = 0 ) in vec2 pos;
layout(location = 1 ) in vec4 col;

out vec4 v_color;


void main()
{
    gl_Position = vec4(pos, 1.0, 1.0);
    v_color = col;
}