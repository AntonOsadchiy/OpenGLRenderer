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
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"


static constexpr int window_width = 1280;
static constexpr int window_height = 720;


int main()
{
	glfwInitialiser::getInstance();
	glfwWindowHandle window{ glfwInitialiser::createWindow(window_width, window_height, "Renderer") };
	glfwMakeContextCurrent(window.get());
	init_glew();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.06f, 0.06f, 0.06f, 0.0f);	

	stbi_set_flip_vertically_on_load(true);

	glm::mat4 projection = glm::perspective(90.f, (float)window_width / window_height, 1.f, -1.f);

	Shader light_source_shader("C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/light_source_vertex.shader",
		"C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/light_source_fragment.shader");
	glm::vec4 initial_light_pos{ 2.0f, 2.0f, 2.0f, 1.0f };
	glm::vec3 light_dir = glm::normalize(glm::vec3{ 0.f, -1.f, -1.f });
	DirectionalLight white_light{
		light_dir,
		//glm::normalize(glm::vec4{0.f } - initial_light_pos),
		glm::vec3{ 1.0f, 1.0f, 1.0f },
		glm::vec3{ 0.1f },
		glm::vec3{ 0.6f },
		glm::vec3{ 0.6f }//,
		//0.09f, 0.032f//,
		//glm::cos(glm::radians(50.0f)), glm::cos(glm::radians(60.0f))
	};

	auto model = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3{ 0.6f }), glm::vec3{ 0.0f });
	Camera cam{ glm::vec3{0.0f, 2.0f, 3.0f}, glm::vec3{0.0f} };
	Shader shader("C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/vertex.shader",
		"C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/fragment.shader");

	shader.bind();
	shader.set_uniform("u_model", model);
	shader.set_uniform("u_view", cam.transform());
	shader.set_uniform("u_projection", projection);
	shader.set_uniform("u_cam_pos", cam.pos());
	shader.add_light(white_light);
	shader.finish_setting_ligths();

	Model backpack{ "C:/dev/src/opengl_renderer/OpenGLRenderer/res/models/backpack/backpack.obj" };


	float scale_factor = 0.97;
	float delta = 0.0009;
	Renderer renderer;
	while (!glfwWindowShouldClose(window.get()))
	{
		if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window.get(), true);

		if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
			cam.move_to(glm::rotate(glm::mat4{ 1.0f }, -delta, { 1.f,0.f,0.f }) * glm::vec4{ cam.pos(), 1.0f });
		if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
			cam.move_to(glm::rotate(glm::mat4{ 1.0f },  delta, { 1.f,0.f,0.f }) * glm::vec4{ cam.pos(), 1.0f });
		if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
			cam.move_to(glm::rotate(glm::mat4{ 1.0f }, -delta, { 0.f,1.f,0.f }) * glm::vec4{ cam.pos(), 1.0f });
		if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
			cam.move_to(glm::rotate(glm::mat4{ 1.0f },  delta, { 0.f,1.f,0.f }) * glm::vec4{ cam.pos(), 1.0f });
		if (glfwGetKey(window.get(), GLFW_KEY_UP) == GLFW_PRESS)
			model = glm::scale(model, glm::vec3{ 1 / scale_factor });
		if (glfwGetKey(window.get(), GLFW_KEY_DOWN) == GLFW_PRESS)
			model = glm::scale(model, glm::vec3{ scale_factor });
	
		shader.set_uniform("u_cam_pos", cam.pos());
		shader.set_uniform("u_model", model);
		shader.set_uniform("u_view", cam.transform());

		renderer.draw(backpack, shader);

		glfwSwapBuffers(window.get());
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	return 0;
}