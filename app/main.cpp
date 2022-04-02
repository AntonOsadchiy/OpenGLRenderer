#include <iostream>
#include <string>
#include <stdint.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <thread>

#include "util.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"


static constexpr int window_width = 1280;
static constexpr int window_height = 720;

int main()
{
	glfwInitialiser::getInstance();
	glfwWindowHandle window{ glfwInitialiser::createWindow(window_width, window_height, "Renderer") };
	glfwMakeContextCurrent(window.get());
	init_glew();

	constexpr std::array vertices_buffer{
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexBuffer vb(vertices_buffer, GL_STATIC_DRAW);
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	VertexArray va(vb, layout);

	constexpr std::array<uint16_t, 6 * 6> indices_buffer{	 0, 1, 2, 3, 4, 5, 6,
															 7, 8, 9,10,11,12,13,
															14,15,16,17,18,19,20,
															21,22,23,24,25,26,27,
															28,29,30,31,32,33,34,
															35}; 
	IndexBuffer ib(indices_buffer, GL_STATIC_DRAW);

	Shader shader("C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/vertex.shader",
		"C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/fragment.shader");

	Texture<GL_TEXTURE_2D> texture("C:/dev/src/opengl_renderer/OpenGLRenderer/res/textures/crate1.png");
	texture.bind();
	shader.set_uniform("u_texture_2d", 0);

	glm::mat4 projection = glm::perspective(103.f, (float)window_width / window_height, 1.f, -1.f);

	float start_angle = 1.f;
	float angle = 0.00025f;
	//float angle = 0.f;
	glm::vec3 axis{ 0.f, 1.f, 0.f };
	float scale = 2.f;
	glm::mat4 model = glm::rotate(glm::scale(glm::mat4(1.f), glm::vec3{ scale, scale, scale }), angle, axis);

	Camera cam({ 0.f, 1.5f, -3.f });
	glm::mat4 mvp = projection * cam.transform() * model;



	Renderer renderer;
	while (!glfwWindowShouldClose(window.get()))
	{
		renderer.clear();

		shader.set_uniform("u_model_view_projection", mvp);
		Renderer::draw(va, ib, shader);

		if (angle < start_angle)
			model = glm::rotate(model, angle, axis);
		mvp = projection * cam.transform() * model;

		glfwSwapBuffers(window.get());
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glfwSetKeyCallback(window.get(), Camera::on_key);
	//auto render = [&]()
	//{
	//	Renderer renderer;
	//	while (!glfwWindowShouldClose(window.get()))
	//	{
	//		renderer.clear();

	//		shader.set_uniform("u_model_view_projection", mvp);
	//		Renderer::draw(va, ib, shader);

	//		if (angle < start_angle)
	//			model = glm::rotate(model, angle, axis);
	//		mvp = projection * cam.transform() * model;

	//		glfwSwapBuffers(window.get());
	//		glfwPollEvents();
	//	}
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//};
	//std::thread renderer_thread( render );
	
	//renderer_thread.join();
	return 0;
}