#pragma once 
#include <GL/glew.h>
#include <string>
#include <array>
#include <unordered_map>
#include <iostream>

#include <glm/glm.hpp>

#include "Material.h"
#include "LightType.h"


class Model;
class Mesh;
class Shader
{
private:
	std::unordered_map<std::string_view, int> m_uniform_location_cache;
	uint32_t m_renderer_id;
	uint32_t m_num_lights = 0;

public:
	Shader(std::string_view, std::string_view);
	~Shader();

	inline void bind()const { glUseProgram(m_renderer_id); }
	inline void unbind()const { glUseProgram(0); }

	int32_t get_uniform_location(std::string_view uniform);

	inline void set_uniform(std::string_view uniform, int32_t n) { glUniform1i(get_uniform_location(uniform), n); }
	inline void set_uniform(std::string_view uniform, float n) { glUniform1f(get_uniform_location(uniform), n); }
	inline void set_uniform(std::string_view uniform, const glm::vec3& data) { glUniform3f(get_uniform_location(uniform), data[0], data[1], data[2]); }
	inline void set_uniform(std::string_view uniform, const glm::vec4& data) { glUniform4f(get_uniform_location(uniform), data[0], data[1], data[2], data[3]); }
	inline void set_uniform(std::string_view uniform, const glm::mat4& data) { glUniformMatrix4fv(get_uniform_location(uniform), 1, GL_FALSE, &data[0][0]); }

	//void set_material(const Material& m);
	//void set_material(std::string_view, const Material& m);

	void set_light(const DirectionalLight&, uint32_t);
	void set_light(const PointLight&, uint32_t);
	void set_light(const SpotLight&, uint32_t);
	void add_light(const DirectionalLight&);
	void add_light(const PointLight&);
	void add_lights(const PointLight*, uint32_t);
	void add_light(const SpotLight&);

	void set_model(const Model&);
	void set_mesh(const Mesh& mesh);

	inline void finish_setting_ligths() { set_uniform("u_n_lights", (int)m_num_lights); }

private:
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator=(Shader&&) = delete;

	static unsigned int create_shader(std::string_view vertex_shader, std::string_view fragment_shader);
	static std::string parse_shader(std::string_view filename);

	void set_light_properties( const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&, uint32_t);
	inline void set_light_pos_and_dir(const glm::vec4&, const glm::vec3&, uint32_t);
	inline void set_light_consts(float, float, float, float, uint32_t);
	inline void set_light_consts(float val, uint32_t index) { set_light_consts(val, val, val, val, index); }
};
