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
	std::cout << glGetString(GL_VERSION) << std::endl;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		std::cout << "failed to initialize glew" << std::endl;

	float vertices_buffer[] = {
		0.5f, 0.5f,
		0.0f, 0.0f,
		-0.5f, 0.5f
	};
	uint32_t vertices;
	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices_buffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0 );
	glEnableVertexAttribArray(0);

	static constexpr auto vertex_shader = std::string_view("#version 330 core\n"
	"\n"
	"layout (location = 0) in vec4 position;"
	"void main()\n"
	"{\n"
	"	gl_Position = position;\n"
	"}\n");

	static constexpr auto fragment_shader = std::string_view("#version 330 core \n"
	"\n"
	"layout (location = 0) out vec4 color;"
	"void main()\n"
	"{\n"
	"	color = vec4(1.0, 0.0, 0.2, 1.0);\n"
	"}\n");

	auto shader_id = Shader::create_shader(vertex_shader, fragment_shader);
	glUseProgram(shader_id);

	while (!glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}

	return 0;
}