#include <iostream>
#include <string>
#include <stdint.h>
#include <GL/glew.h>

#include "util.h"
#include "Bresenham.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Renderer.h"
#include "Texture.h"

int main()
{
	glfwInitialiser::getInstance();
	glfwWindowHandle window{ glfwInitialiser::createWindow(1280, 720, "Renderer") };
	glfwMakeContextCurrent(window.get());
	init_glew();

	constexpr std::array vertices_buffer{	 0.5f,  0.5f, 1.0f, 1.0f,
											-0.5f,  0.5f, 0.0f, 1.0f,
											-0.5f, -0.5f, 0.0f, 0.0f,
											 0.5f, -0.5f, 1.0f, 0.0f };

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexArray va;
	VertexBuffer vb(vertices_buffer, GL_STATIC_DRAW);

	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.add_buffer(vb, layout);

	constexpr std::array<uint16_t, 6> indices_buffer{ 0, 1, 2, 2, 3, 0 };
	IndexBuffer ib(indices_buffer, GL_STATIC_DRAW);

	Shader shader(	"C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/vertex.shader",
					"C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/fragment.shader");

	Texture texture("C:/Users/1voic/source/repos/OpenGLRenderer/res/textures/Portal-Transparent-PNG.png");
	texture.bind();
	shader.set_uniform("u_texture", 0);

	Renderer renderer;
	while (!glfwWindowShouldClose(window.get()))
	{	
		shader.set_uniform("u_color", std::array{ 0.3f, 0.3f, 0.3f, 1.0f });
		renderer.draw(va, ib, shader);

		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	return 0;
}