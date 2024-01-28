#include "Shader.h"
#include "Model.h"
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

void Shader::set_model(const Model& model)
{
	for (auto& mesh : model.meshes())
		set_mesh(mesh);
}

void Shader::set_mesh(const Mesh& mesh)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (int i = 0; i < mesh.textures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = mesh.textures()[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); 
		else if (name == "texture_height")
			number = std::to_string(heightNr++);
		set_uniform((std::string{ "u_material." } + name + number).c_str(), i);
		set_uniform("u_material.snininess", 128);

		glBindTexture(GL_TEXTURE_2D, mesh.textures()[i].id);
	}
}


void Shader::set_light(const SpotLight&, uint32_t)
{
}

void Shader::add_lights(const PointLight* lights, uint32_t n)
{	
	for (int i = 0; i < n; i++)
		add_light(lights[i]);
}

//void Shader::set_material(const Material& m)
//{
//	m.diffuse_map.bind(0);
//	set_uniform("u_material.diffuse_map", 0);
//	m.specular_map.bind(1);
//	set_uniform("u_material.specular_map", 1);
//	set_uniform("u_material.shininess", m.shininess);
//}

void Shader::add_light(const DirectionalLight& light)
{
	set_light_properties(light.color(), light.ambient(), light.diffuse(), light.specular(), m_num_lights);
	set_light_pos_and_dir(glm::vec4(0.0f), light.direction(), m_num_lights);
	set_light_consts(-1.0f, m_num_lights);

	m_num_lights++;
}


void Shader::add_light(const PointLight& light)
{
	set_light_properties(light.color(), light.ambient(), light.diffuse(), light.specular(), m_num_lights);
	set_light_pos_and_dir(light.pos(), glm::vec3(0.f), m_num_lights);
	set_light_consts(light.attenuation_linear(), light.attenuation_quadratic(), -1.0f, -1.0f, m_num_lights);

	m_num_lights++;
}

void Shader::add_light(const SpotLight& light)
{
	set_light_properties(light.color(), light.ambient(), light.diffuse(), light.specular(), m_num_lights);
	set_light_pos_and_dir(light.pos(), light.direction(), m_num_lights);
	set_light_consts(light.attenuation_linear(), light.attenuation_quadratic(), light.angle(), light.outer_angle(), m_num_lights);

	m_num_lights++;
}


std::string lights(uint32_t i)
{
	std::stringstream ss;
	ss << "u_lights[" << std::to_string(i) << "].";
	return ss.str();
}


void Shader::set_light_properties(const glm::vec3& color,
	const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, uint32_t index)
{
	std::string l = lights(index);
	set_uniform(l + "color", color);

	set_uniform(l + ("ambient_comp"), ambient);
	set_uniform(l + ("diffuse_comp"), diffuse);
	set_uniform(l + ("specular_comp"), specular);
}

void Shader::set_light_pos_and_dir(const glm::vec4& pos, const glm::vec3& direction, uint32_t index)
{
	std::string l = lights(index);
	set_uniform(l + ("pos"), pos);
	set_uniform(l + ("direction"), direction);
}

void Shader::set_light_consts(float attenuation_lin, float attenuatin_quad, float spot_angle, float outer_angle, uint32_t index)
{
	std::string l = lights(index);
	set_uniform(l + ("attenuation_linear"), attenuation_lin);
	set_uniform(l + ("attenuation_quadratic"), attenuatin_quad);

	set_uniform(l + ("spot_angle"), spot_angle);
	set_uniform(l + ("spot_outer_angle"), outer_angle);
}

unsigned int Shader::create_shader(string_view vertex_shader, string_view fragment_shader)
{
	auto program = glCreateProgram();
	auto vertex_id = compile_shader(GL_VERTEX_SHADER, vertex_shader.data());
	auto fragment_id = compile_shader(GL_FRAGMENT_SHADER, fragment_shader.data());

	glAttachShader(program, vertex_id);
	glAttachShader(program, fragment_id);
	glLinkProgram(program);

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
	glValidateProgram(program);
	return program;
}


std::string Shader::parse_shader(std::string_view filepath)
{
	std::ifstream stream(filepath.data());
	if (!stream.is_open())
	{
		std::cout << "Failed to open " + std::string(filepath.data()) << std::endl;
	}
	std::string line;
	std::stringstream ss;
	while (getline(stream, line))
		ss << line << '\n';

	return ss.str();
}

Shader::Shader(std::string_view vertex_filepath, std::string_view fragment_fileapth)
{
	m_renderer_id = Shader::create_shader(Shader::parse_shader(vertex_filepath), Shader::parse_shader(fragment_fileapth));
}

Shader::~Shader()
{
	glDeleteProgram(m_renderer_id);
}

int32_t Shader::get_uniform_location(std::string_view uniform)
{
	if (m_uniform_location_cache.find(uniform) != m_uniform_location_cache.end())
		return m_uniform_location_cache[uniform];
	return m_uniform_location_cache[uniform] = glGetUniformLocation(m_renderer_id, uniform.data());
}
