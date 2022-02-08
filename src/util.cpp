#include "util.h"

void gl_debug_output(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "message: " << message << std::endl;
    std::cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";
    switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
}

void setup_debug_callback(DEBUGPROC fun)
{
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(gl_debug_output, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		puts("Debug");
	}
	else
		puts("Debug for OpenGL not supported by your system!");
}


void init_glew()
{
    glewExperimental = GL_TRUE;
    auto err = glewInit();
#ifndef NDEBUG
    if (err != GLEW_OK)
    {
        std::cout << "failed to initialize glew" << std::endl;
        return;
    }
    setup_debug_callback(gl_debug_output);
    std::cout << glGetString(GL_VERSION) << std::endl;
#endif
}


glfwInitialiser* glfwInitialiser::m_instance = nullptr;

glfwInitialiser* glfwInitialiser::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new glfwInitialiser();
	}
	return m_instance;
}

GLFWwindow* glfwInitialiser::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    auto window = glfwCreateWindow(width, height, title, monitor, share);
    if (!window)
        std::cout << "window creation error" << std::endl;
    return window;
#else
    return glfwCreateWindow(width, height, title, monitor, share);
#endif

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

