#include "VertexLayout.h"
#include <cassert>

uint32_t VertexBufferLayout::Element::sizeof_type() const
{
	switch (type)
	{
	case GL_FLOAT: return sizeof(GLfloat);
	case GL_UNSIGNED_INT: return sizeof(GLuint);
	}
	assert(false);
	return -1;
}