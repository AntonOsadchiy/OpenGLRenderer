#include "Mesh.h"

Mesh::Mesh(const float* vertex_data, uint32_t len1, const uint32_t* indices_data, uint32_t len2)
	:m_vertices(len1 / Vertex::elems_per_vertex), m_indices(len2),
	m_vertex_buffer(vertex_data, len1), m_index_buffer(indices_data, len2)
{
	assert(len1 % Vertex::elems_per_vertex == 0);
	uint32_t n_vertices = len1 / Vertex::elems_per_vertex;

	for (int i = 0; i < n_vertices; i++)
	{
		uint32_t n = i * Vertex::elems_per_vertex;
		m_vertices.at(i) = Vertex{glm::vec3{vertex_data[n], vertex_data[n + 1], vertex_data[n + 2]},
						glm::vec3{vertex_data[n+3], vertex_data[n+4], vertex_data[n+5]},
						glm::vec2{vertex_data[n+6], vertex_data[n+7]} };
	}

	for (int i = 0; i < len2; i++)
		m_indices.at(i) = indices_data[i];

	m_vertex_array.add_buffer( m_vertex_buffer, VertexBufferLayout{3,3,2});
}

void Mesh::bind()
{
	va().bind();
	ib().bind();
}
