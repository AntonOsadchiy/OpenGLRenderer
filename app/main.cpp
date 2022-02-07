#include <iostream>
#include <string>
#include <GL/glew.h>
#include <stdint.h>

#include "util.h"
#include "Bresenham.h"
#include "Shader.h"

int main()
{
	glfwInitialiser::getInstance();

	glfwWindowHandle window{ glfwInitialiser::createWindow(1280, 720, "Renderer") };
	if (!window.get())
		std::cout << "window creation error" << std::endl;

	glfwMakeContextCurrent(window.get());

	glewExperimental = GL_TRUE;
	auto err = glewInit();
	if (err != GLEW_OK)
		std::cout << "failed to initialize glew" << std::endl;

#ifndef NDEBUG
	setup_debug_callback(gl_debug_output);
#endif
	std::cout << glGetString(GL_VERSION) << std::endl;


	float vertices_buffer[] = {
		0.5f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};
	unsigned int indices_buffer[] = { 0, 1, 2, 2, 3, 0 };

	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uint32_t vertices_id;
	glGenBuffers(1, &vertices_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_id);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertices_buffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0 );
	glEnableVertexAttribArray(0);

	uint32_t indices_id;
	glGenBuffers(1, &indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices_buffer, GL_STATIC_DRAW);


	auto shader_id = Shader::create_shader(
		Shader::parse_shader("C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/vertex.shader"),
		Shader::parse_shader("C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/fragment.shader"));
	glUseProgram(shader_id);

	auto color_location = glGetUniformLocation(shader_id, "u_color");
	glUniform4f(color_location, 0.9f, 0.05f, 0.25f, 1.0f);

	while (!glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}

	return 0;
}