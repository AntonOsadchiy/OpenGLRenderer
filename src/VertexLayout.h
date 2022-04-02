#pragma once 

#include <GL/glew.h>
#include <stdint.h>
#include <vector>
#include <iostream>

class VertexBufferLayout
{
public:
	struct Element
	{
		uint32_t type;
		uint32_t len;
		bool normalized;

		uint32_t sizeof_type() const;
	};

private:
	std::vector<Element> m_elements;
	uint32_t m_stride = 0;
public:

	template<typename T>
	void push(uint32_t len)
	{
		//static_assert(false);
		std::cout << "bad push\n";
	}

	template<>
	void push<float>(uint32_t len)
	{
		m_elements.push_back(Element{ GL_FLOAT, len, GL_FALSE });
		m_stride += len * m_elements[m_elements.size() - 1].sizeof_type();
	}

	template<>
	void push<uint32_t>(uint32_t len)
	{
		m_elements.push_back(Element{ GL_UNSIGNED_INT, len, GL_TRUE });
		m_stride += len * m_elements[m_elements.size() - 1].sizeof_type();
	}

	inline uint32_t stride()const { return m_stride; }

	inline const Element& operator[](int index) const { return m_elements[index]; }
	inline const std::vector<Element>& elements() const { return m_elements; }
};