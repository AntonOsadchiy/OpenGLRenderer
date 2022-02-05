#include "Shader.h"
#include <iostream>

using namespace std;

unsigned int compile_shader(unsigned int type, const char* source)
{
	auto shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, nullptr);
	glCompileShader(shader_id);

	auto shader_compiled = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE)
	{
		int log_size = 0;
		char message[1024];
		glGetShaderInfoLog(shader_id, 1024, &log_size, message);
		cout << message << endl;
		glDeleteShader(shader_id);
		return GL_FALSE;
	}

	return shader_id;
}

unsigned int Shader::create_shader(string_view vertex_shader, string_view fragment_shader)
{
	auto program = glCreateProgram();
	auto vertex_id = compile_shader(GL_VERTEX_SHADER, vertex_shader.data());
	auto fragment_id = compile_shader(GL_FRAGMENT_SHADER, fragment_shader.data());

	glAttachShader(program, vertex_id);
	glAttachShader(program, fragment_id);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

	int program_linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		int log_size = 0;
		char message[1024];
		glGetProgramInfoLog(program, 1024, &log_size, message);
		cout << message << endl;
	}

	return program;
}