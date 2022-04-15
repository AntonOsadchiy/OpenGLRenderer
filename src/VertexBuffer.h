#pragma once
#include <stdint.h>
#include <GL/glew.h>
#include <type_traits>
#include <array>

class VertexBuffer
{
private:
	uint32_t m_renderer_id;

public:
	explicit VertexBuffer():m_renderer_id(0) {}

	template<typename T, int N>
	VertexBuffer(const std::array<T, N>& vertices, int param = GL_STATIC_DRAW) { init( vertices.data(), sizeof(T) * N, param); }

	template<typename T>
	VertexBuffer(const T* vertices, uint32_t len, int param = GL_STATIC_DRAW) { init(vertices, sizeof(T) * len, param); }




	VertexBuffer(VertexBuffer&&) = default;
	VertexBuffer& operator=(VertexBuffer&&) = default;

	~VertexBuffer();

	inline void bind()const { glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id); }
	inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
	void init(const void*, uint32_t, int);

	VertexBuffer(const VertexBuffer&) = default;
	VertexBuffer& operator=(const VertexBuffer&) = default;
};

