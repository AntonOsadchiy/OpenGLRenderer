#pragma once 
#include <GL/glew.h>
#include <string>
#include <stdint.h>

#include "vendor/stb_image.h"

class Texture
{
private:
	uint32_t m_renderer_id;
	std::string m_filepath;
	uint8_t* m_local_buffer;
	int32_t m_width, m_height, m_BPP;

public:
	Texture(std::string_view filepath);
	~Texture();

	void bind(int32_t slot = 0)const;
	inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	inline auto width() const { return m_width; }
	inline auto height() const { return m_height; }
};