#pragma once 

#include <stdint.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>

class GLFWwindow;

class Camera
{
private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_up;
	float m_speed;

public:
	Camera(glm::vec3 pos , glm::vec3 target = glm::vec3{ 0.f,0.f,0.f }, float speed = 1.f)
		:m_pos(pos), m_target(target), m_up(0.f, 1.f, 0.f), m_speed(speed)
	{
	}

	~Camera() = default;

	inline auto rignt() const { return glm::cross(m_up, m_target); }
	inline auto left() const { return glm::cross(m_target, m_up); }


	inline glm::mat4 transform() const { return glm::lookAt(m_pos, m_target, m_up); }

	inline void move(const glm::vec3& delta)  { m_pos += delta * m_speed; }
	inline void move_to(const glm::vec3& pos) { m_pos = pos; }

	inline auto pos() const { return m_pos; }

	inline float& speed() { return m_speed; }
	inline float speed() const { return m_speed; }
};