#include "VertexBuffer.h"

void VertexBuffer::init(const void* data, uint32_t size, int param)
{
	glCreateBuffers(1, &m_renderer_id);
	glNamedBufferData(m_renderer_id, size, data, param);
}

VertexBuffer::~VertexBuffer()
{
	unbind();
	glDeleteBuffers(1, &m_renderer_id);
}
