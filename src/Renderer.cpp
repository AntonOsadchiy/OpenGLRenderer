#include "Renderer.h"
#include "Model.h"

void Renderer::draw(const Model& model, Shader& shader)
{
	for (auto& mesh : model.meshes())
	{
		shader.bind();
		shader.set_mesh(mesh);
		mesh.va().bind();
		mesh.ib().bind();
		glDrawElements(GL_TRIANGLES, mesh.ib().len(), mesh.ib().openGL_type(), nullptr);
	}
}