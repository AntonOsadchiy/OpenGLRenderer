#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Light
{
private:
	glm::vec3 m_color;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

public:
	Light(const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		:m_color{ color }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular } {}

	const glm::vec3& color() const { return m_color; }
	const glm::vec3& ambient() const { return m_ambient; }
	const glm::vec3& diffuse() const { return m_diffuse; }
	const glm::vec3& specular() const { return m_specular; }

};

struct PointLight : public Light
{
private:
	glm::vec4 m_pos;
	float m_attenuation_linear;
	float m_attenuation_quadratic;

public:
	PointLight(const glm::vec4& pos, const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float attenuation_linear, float attenuation_quadratic)
		:Light{ color, ambient, diffuse, specular }, m_pos{ pos },
		 m_attenuation_linear{ attenuation_linear }, m_attenuation_quadratic{ attenuation_quadratic }{}

	inline glm::vec4& pos() { return m_pos; }
	inline const glm::vec4& pos() const { return m_pos; }
	inline float attenuation_linear() const { return m_attenuation_linear; }
	inline float attenuation_quadratic() const { return m_attenuation_quadratic; }
};

struct DirectionalLight : public Light
{
private:
	glm::vec3 m_direction;

public:
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		:Light{ color, ambient, diffuse, specular }, m_direction{ direction } {}

	inline const glm::vec3& direction() const { return m_direction; }
};

struct SpotLight : public PointLight
{
private:
	glm::vec3 m_direction;
	float m_angle;
	float m_outer_angle;

public:
	SpotLight(const glm::vec4& pos, const glm::vec3& direction, const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float attenuation_linear, float attenuation_quadratic, float angle, float outer_angle)
		:PointLight{ pos, color, ambient, diffuse, specular, attenuation_linear, attenuation_quadratic },
		m_direction{ direction }, m_angle{ angle }, m_outer_angle{ outer_angle } {}

	inline const glm::vec3& direction() const { return m_direction; }
	inline glm::vec3& direction() { return m_direction; }
	inline float angle() const { return m_angle; }
	inline float outer_angle() const { return m_outer_angle; }
};