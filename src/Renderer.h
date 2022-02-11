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
	static void draw(const VertexArray& va, const IndexBuffer<T>& ib, const Shader& shader)
	{
		va.bind();
		ib.bind();
		shader.bind();
		glDrawElements(GL_TRIANGLES, ib.len(), ib.openGL_type(), nullptr);
	}


	inline static void draw_points(const VertexArray& va, uint32_t num_points)
	{
		va.bind();
		glDrawArrays(GL_POINTS, 0, num_points);
	}
};