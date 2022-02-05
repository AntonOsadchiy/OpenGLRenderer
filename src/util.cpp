#include "util.h"

glfwInitialiser* glfwInitialiser::m_instance = nullptr;

glfwInitialiser* glfwInitialiser::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new glfwInitialiser();
	}
	return m_instance;
}


glfwInitialiser::glfwInitialiser()
{
	if (!glfwInit())
	{
		std::cout << "glfw init error" << std::endl;
	}
	glfwSetErrorCallback(error_callback);
}

glfwInitialiser::~glfwInitialiser()
{
	glfwTerminate();
}

void glfwInitialiser::error_callback(int error, const char* description)
{
	std::cout << "glfw error " << error << " " << description << std::endl;
}