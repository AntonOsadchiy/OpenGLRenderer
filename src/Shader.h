#pragma once 
#include <GL/glew.h>
#include <string>
#include <array>
#include <unordered_map>
#include <iostream>

#include <glm/glm.hpp>
class Shader
{
private:
	uint32_t m_renderer_id;
	std::unordered_map<std::string_view, int> m_uniform_location_cache;

public:
	Shader(std::string_view, std::string_view);
	~Shader();

	inline void bind()const { glUseProgram(m_renderer_id); }
	inline void unbind()const { glUseProgram(0); }

	int32_t get_uniform_location(std::string_view uniform);

	template<typename T>
	void set_uniform(std::string_view, const T&)
	{
		//static_assert(false);
		std::cout << "bad set_uniform\n";
	}

	template<> void set_uniform<int32_t>(std::string_view uniform, const int32_t& n)
	{
		bind();
		glUniform1i(get_uniform_location(uniform), n);
	}

	template<> void set_uniform<glm::vec4>(std::string_view uniform, const glm::vec4& data)
	{
		bind();
		glUniform4f(get_uniform_location(uniform), data[0], data[1], data[2], data[3]);
	}

	template<>void set_uniform<glm::mat4>(std::string_view uniform, const glm::mat4& data)
	{
		bind();
		glUniformMatrix4fv(get_uniform_location(uniform), 1, GL_FALSE, &data[0][0]);
	}

private:
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator=(Shader&&) = delete;

	static unsigned int create_shader(std::string_view vertex_shader, std::string_view fragment_shader);

	static std::string parse_shader(std::string_view filename);
};
