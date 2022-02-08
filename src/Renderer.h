#pragma once 
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer
{
public:
	inline void clear()const { glClear(GL_COLOR_BUFFER_BIT); }

	template<typename T>
	void draw(const VertexArray& va, const IndexBuffer<T>& ib, const Shader& shader)const
	{
		clear();
		va.bind();
		ib.bind();
		shader.bind();
		glDrawElements(GL_TRIANGLES, ib.len(), ib.openGL_type(), nullptr);
	}
};