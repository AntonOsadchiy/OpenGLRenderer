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

	static VertexBufferLayout layout; 
};


class Mesh
{
private:
	static constexpr uint32_t floats_per_vertex = sizeof(Vertex) / sizeof(float);


	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;

	std::vector<AssimpTexture> m_textures;

	std::unique_ptr<VertexBuffer> m_vertex_buffer = nullptr;
	std::unique_ptr<IndexBuffer<uint32_t>> m_index_buffer = nullptr;
	std::unique_ptr<VertexArray> m_vertex_array = nullptr;
	

	Mesh(const Mesh&) = default;
	Mesh& operator=(const Mesh&) = default;
public:
	Mesh() {} 
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<AssimpTexture>& textures);
	Mesh(const float* vertex_data, uint32_t len1, const uint32_t* indices_data, uint32_t len2);

	void start_open_gl();

	Mesh(Mesh&&) = default;
	Mesh& operator=(Mesh&&) = default;

	inline void set_textures(const std::vector<AssimpTexture>& textures) { m_textures = textures; }
	inline const std::vector<AssimpTexture>& textures() const { return m_textures; }

	inline const VertexArray& va() const { return *m_vertex_array; }
	inline const IndexBuffer<uint32_t>& ib() const { return *m_index_buffer; }

	void bind();
};

