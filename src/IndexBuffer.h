#pragma once 
#include <stdint.h>
#include <GL/glew.h>
#include <type_traits>
#include <array>
#include <iostream>

template<typename T>
class IndexBuffer
{
private:
	using uint_type = T;
	uint32_t m_renderer_id;
	uint32_t m_length;

	IndexBuffer(const IndexBuffer&) = default;
	IndexBuffer& operator=(const IndexBuffer&) = default;
public:
	explicit IndexBuffer():m_renderer_id(0), m_length(0) {}

	template<int N>
	IndexBuffer(const std::array<uint_type, N>& indices, int param = GL_STATIC_DRAW):m_length(N) { init(indices.data(), sizeof(uint_type) * N, param); }

	IndexBuffer(IndexBuffer&&) = default;
	IndexBuffer& operator=(IndexBuffer&&) = default;
	

	IndexBuffer(const uint_type* indices, uint32_t n, int param = GL_STATIC_DRAW):m_length(n) { init(indices, sizeof(uint_type) * n, param); }

	~IndexBuffer()
	{
		unbind();
		glDeleteBuffers(1, &m_renderer_id);
	}

	inline void bind()const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id); }
	inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	inline uint32_t len() const { return m_length; }


	constexpr inline auto openGL_type() const
	{
		if constexpr(sizeof(uint_type) == 1)
			return GL_UNSIGNED_BYTE;
		if constexpr(sizeof(uint_type) == 2)
			return GL_UNSIGNED_SHORT;
		if constexpr(sizeof(uint_type) == 4)
			return GL_UNSIGNED_INT;
	}
private:
	void init(const uint_type* data, uint32_t size, int param)
	{
		glCreateBuffers(1, &m_renderer_id);
		glNamedBufferData(m_renderer_id, size, data, param);
	}


};