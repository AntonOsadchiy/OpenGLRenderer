#pragma once 
#include <GL/glew.h>
#include <string>


class Shader
{
public:

	static unsigned int create_shader(std::string_view vertex_shader, std::string_view fragment_shader);

	static std::string parse_shader(std::string_view filename);
};
