#include "Texture.h"



//template<uint32_t Type>
//Texture<Type>::Texture(std::string_view filepath)
//	:m_renderer_id(0), m_filepath(filepath), m_local_buffer(nullptr), m_width(0), m_height(0), m_BPP(0)
//{
//	stbi_set_flip_vertically_on_load(1);
//	m_local_buffer = stbi_load(filepath.data(), &m_width, &m_height, &m_BPP, 4);
//
//	glGenTextures(1, &m_renderer_id);
//	glBindTexture(type(), m_renderer_id);
//
//	glTexParameteri(type(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(type(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(type(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(type(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	glTexImage2D(type(), 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
//
//	unbind();
//}
//
//template<uint32_t Type>
//Texture<Type>::~Texture()
//{
//	unbind();
//	if (m_local_buffer)
//		stbi_image_free(m_local_buffer);
//	glDeleteTextures(1, &m_renderer_id);
//}
//
//template<uint32_t Type>
//void Texture<Type>::bind(int32_t slot) const
//{
//	glActiveTexture(GL_TEXTURE0 + slot);
//	glBindTexture(type(), m_renderer_id);
//}
