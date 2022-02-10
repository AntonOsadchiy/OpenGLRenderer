#pragma once 
#include <stdint.h>


class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	uint32_t m_renderer_id;

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;
public:
	VertexArray();
	VertexArray(const VertexBuffer&, const VertexBufferLayout&);
	~VertexArray();

	void bind() const;
	void unbind() const;

	void add_buffer(const VertexBuffer&, const VertexBufferLayout&);

};