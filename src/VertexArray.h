#pragma once 
#include <stdint.h>


class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	uint32_t m_renderer_id;

	VertexArray(const VertexArray&) = default;
	VertexArray& operator=(const VertexArray&) = default;
	
public:
	VertexArray();
	VertexArray(const VertexBuffer&, const VertexBufferLayout&);



	VertexArray(VertexArray&&) = default;
	VertexArray& operator=(VertexArray&&) = default;

	~VertexArray();

	void bind() const;
	void unbind() const;

	void add_buffer(const VertexBuffer&, const VertexBufferLayout&);

};