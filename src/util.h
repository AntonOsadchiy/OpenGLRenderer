#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using DEBUGPROC = void (APIENTRY*)(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);


void gl_debug_output(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);

void setup_debug_callback(DEBUGPROC fun);


class glfwInitialiser
{
public:
	
	static glfwInitialiser* getInstance();

	static GLFWwindow* createWindow(
		int		width,
		int		height,
		const char* title = "window",
		GLFWmonitor* monitor = NULL,
		GLFWwindow* share = NULL);


private:
	static glfwInitialiser* m_instance;

	glfwInitialiser();
	~glfwInitialiser();

	glfwInitialiser(const glfwInitialiser&) = delete;
	glfwInitialiser& operator=(const glfwInitialiser&) = delete;
	glfwInitialiser(glfwInitialiser&&) = delete;
	glfwInitialiser& operator=(glfwInitialiser&&) = delete;

	static void error_callback(int, const char*);
};


struct glfwWindowHandle
{
	GLFWwindow* m_window;

	inline glfwWindowHandle(GLFWwindow* window) : m_window(window) {} ;
	~glfwWindowHandle() { glfwDestroyWindow(m_window); };

	glfwWindowHandle(const glfwWindowHandle& ) = default;
	glfwWindowHandle(glfwWindowHandle&&) = default;
	glfwWindowHandle& operator=(const glfwWindowHandle&) = default;
	glfwWindowHandle& operator=( glfwWindowHandle&&) = default;

	inline GLFWwindow* get() { return m_window; }
	inline int width() const { int width; int height; glfwGetWindowSize(m_window, &width, &height);  return width; }
	inline int height() const { int width; int height; glfwGetWindowSize(m_window, &width, &height);  return height; }
};