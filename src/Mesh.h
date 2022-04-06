#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "VertexLayout.h"

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tex_coords;
	static constexpr uint32_t elems_per_vertex = 8;
};


class Mesh
{
private:

	using tex_vector = std::vector<Texture<GL_TEXTURE_2D>>;

	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;

	std::unique_ptr<Material> m_material = nullptr;

	VertexBuffer m_vertex_buffer;
	IndexBuffer<uint32_t> m_index_buffer;
	VertexArray m_vertex_array;
	
public:
	Mesh(const float* vertex_data, uint32_t len1, const uint32_t* indices_data, uint32_t len2);


	inline const VertexArray& va() const { return m_vertex_array; }
	inline const IndexBuffer<uint32_t>& ib() const { return m_index_buffer; }

	inline void add_material(std::string_view tex1, std::string_view tex2, float shininess)
	{
		auto material = std::make_unique<Material>(tex1, tex2, shininess);
		m_material = std::move(material);
	}
	inline bool material_is_valid() const { return !(!m_material); }
	inline const Material& material() const { return *m_material; }

	void bind();
};

