#include <iostream>
#include <string>
#include <stdint.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "util.h"
#include "Bresenham.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Renderer.h"
#include "Texture.h"


static constexpr int window_width = 1280;
static constexpr int window_height = 720;

int main()
{
	glfwInitialiser::getInstance();
	glfwWindowHandle window{ glfwInitialiser::createWindow(window_width, window_height, "Renderer") };
	glfwMakeContextCurrent(window.get());
	init_glew();

	constexpr std::array vertices_buffer{	 300.f,  300.f, 1.0f, 1.0f, 1.f, 0.f, 0.f, 1.f,
											-300.f,  300.f, 0.0f, 1.0f, 0.f, 0.f, 1.f, 1.f,
											-300.f, -300.f, 0.0f, 0.0f, 1.f, 0.f, 0.f, 1.f,
											 300.f, -300.f, 1.0f, 0.0f, 0.f, 1.f, 0.f, 1.f };

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexBuffer vb(vertices_buffer, GL_STATIC_DRAW);
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	layout.push<float>(4);
	VertexArray va(vb, layout);

	constexpr std::array<uint16_t, 6> indices_buffer{ 0, 1, 2, 2, 3, 0 };
	IndexBuffer ib(indices_buffer, GL_STATIC_DRAW);

	Shader shader(	"C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/vertex.shader",
					"C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/fragment.shader");

	Texture texture("C:/Users/1voic/source/repos/OpenGLRenderer/res/textures/Portal-Transparent-PNG.png");
	texture.bind();
	shader.set_uniform("u_texture", 0);

	glm::mat4 projection = glm::ortho(0.f, (float)window_width, 0.f, (float)window_height, -1.0f, 1.0f);
	float angle = 0.01f;
	glm::vec3 axis{ 0.f, 0.f, 400.f };
	glm::mat4 model = glm::rotate(glm::mat4(1.f), angle, axis);
	glm::mat4 view = glm::translate(glm::mat4(1.f), {600.f, 400.f, 0.f});
	glm::mat4 mvp = projection * view *  model;


	Renderer renderer;
	while (!glfwWindowShouldClose(window.get()))
	{	
		shader.set_uniform("u_model_view_projection", mvp);
		//shader.set_uniform("u_color", glm::vec4{ 0.15f, 0.15f, 0.15f, 1.0f });
		renderer.draw(va, ib, shader);

		model = glm::rotate(model, angle, axis);
		mvp = projection * view * model;

		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	return 0;
}