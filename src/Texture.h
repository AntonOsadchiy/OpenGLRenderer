#pragma once 
#include <GL/glew.h>
#include <string>
#include <stdint.h>

#include "vendor/stb_image.h"


template<uint32_t Type>
class Texture
{
private:
	uint32_t m_renderer_id;
	std::string m_filepath;
	uint8_t* m_local_buffer;
	int32_t m_width, m_height, m_BPP;


	Texture(const Texture<Type>&) = delete;
	Texture<Type>& operator=(const Texture<Type>&) = delete;
public:

	inline constexpr uint32_t type()const { return Type; }
	
	Texture() :m_renderer_id(-1), m_filepath(), m_local_buffer(nullptr), m_width(0), m_height(0), m_BPP(0) {}

	Texture(std::string_view filepath) : m_renderer_id(0), m_filepath(filepath), m_local_buffer(nullptr), m_width(0), m_height(0), m_BPP(0) 
	{ load_texture(filepath); }

	Texture(Texture<Type>&& tex) : m_renderer_id(tex.m_renderer_id), m_filepath(std::move(tex.m_filepath)), m_local_buffer(nullptr),
		m_width(tex.m_width), m_height(tex.m_height), m_BPP(tex.m_BPP)
	{
		std::swap(m_local_buffer, tex.m_local_buffer);
	}

	Texture<Type>& operator=(Texture<Type>&& tex)
	{
		if (m_local_buffer == tex.m_local_buffer)
			return *this;
		m_renderer_id = std::move(tex.m_renderer_id);
		m_filepath = std::move(tex.m_filepath);
		delete[] m_local_buffer;
		m_local_buffer = nullptr;
		std::swap(m_local_buffer, tex.m_local_buffer);
		m_width = tex.m_width;
		m_height = tex.m_height;
		m_BPP = tex.m_BPP;
	}

	~Texture()
	{
		unbind();
		if (m_local_buffer)
			stbi_image_free(m_local_buffer);
		glDeleteTextures(1, &m_renderer_id);
	}

	void set(std::string filepath)
	{
		m_filepath = std::move(filepath);
		load_texture(m_filepath);
	}

	void bind(int32_t slot)const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(type(), m_renderer_id);
	}
	inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	inline auto width() const { return m_width; }
	inline auto height() const { return m_height; }

private:
	void load_texture(std::string_view filepath)
	{
		stbi_set_flip_vertically_on_load(1);
		m_local_buffer = stbi_load(filepath.data(), &m_width, &m_height, &m_BPP, 4);

		glGenTextures(1, &m_renderer_id);
		glBindTexture(type(), m_renderer_id);

		glTexParameteri(type(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(type(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(type(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(type(), 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);

		unbind();
	}
};

using Texture2D = Texture<GL_TEXTURE_2D>;

struct AssimpTexture {
	unsigned int id;
	std::string type;
	std::string path;
};