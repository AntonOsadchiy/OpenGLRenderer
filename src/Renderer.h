#pragma once 
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"


class Renderer
{
public:
	//inline void clear()const { glClear(GL_COLOR_BUFFER_BIT); }

	template<typename T>
	void draw(const VertexArray& va, const IndexBuffer<T>& ib, const Shader& shader)
	{
		va.bind();
		ib.bind();
		shader.bind();
		glDrawElements(GL_TRIANGLES, ib.len(), ib.openGL_type(), nullptr);
	}

	inline void draw(const Mesh& mesh, Shader& shader)
	{
		if (mesh.material_is_valid())
			int i = 0;
		glDrawElements(GL_TRIANGLES, mesh.ib().len(), mesh.ib().openGL_type(), nullptr);
	}
};