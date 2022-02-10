#include "VertexArray.h"
#include "VertexLayout.h"
#include "VertexBuffer.h"




VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_renderer_id);
}

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	glGenVertexArrays(1, &m_renderer_id);
	add_buffer(vb, layout);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_renderer_id);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_renderer_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	void* offset = 0;
	for (uint32_t i = 0; i < layout.elements().size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, layout[i].len, layout[i].type, layout[i].normalized, layout.stride(), offset);
		offset = (char*)offset + (layout[i].len * layout[i].sizeof_type());
	}
}
