#include <iostream>
#include <string>
#include <stdint.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

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

	//constexpr std::array vertices_buffer{	 300.f,  300.f, 1.0f, 1.0f, 1.f, 0.f, 0.f, 1.f,
	//										-300.f,  300.f, 0.0f, 1.0f, 0.f, 0.f, 1.f, 1.f,
	//										-300.f, -300.f, 0.0f, 0.0f, 1.f, 0.f, 0.f, 1.f,
	//										 300.f, -300.f, 1.0f, 0.0f, 0.f, 1.f, 0.f, 1.f };
	constexpr std::array vertices_buffer{
		 100.f,  100.f,  100.f,	 1.f, 0.f, 0.f, 1.f, //0
		-100.f,  100.f, -100.f,	 1.f, 0.f, 0.f, 1.f, //1
		-100.f,  100.f,  100.f,	 1.f, 0.f, 0.f, 1.f, //2
		 100.f, -100.f, -100.f,	 0.f, 0.f, 1.f, 1.f, //3
		-100.f, -100.f, -100.f,	 0.f, 0.f, 1.f, 1.f, //4
		 100.f,  100.f, -100.f,	 0.f, 0.f, 1.f, 1.f, //5
		 100.f, -100.f,  100.f,	 1.f, 0.f, 0.f, 1.f, //6
		-100.f, -100.f,  100.f,	 0.f, 0.f, 1.f, 1.f  //7
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexBuffer vb(vertices_buffer, GL_STATIC_DRAW);
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(4);
	VertexArray va(vb, layout);

	constexpr std::array<uint16_t, 6 * 6> indices_buffer{ 0, 1, 2, 1, 3, 4,   
														5, 6, 3, 7, 3, 6,  
														2, 4, 7, 0, 7, 6,   
														0, 5, 1, 1, 5, 3,  
														5, 0, 6, 7, 4, 3, 
														2, 1, 4, 0, 2, 7 }; 
	IndexBuffer ib(indices_buffer, GL_STATIC_DRAW);

	Shader shader("C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/vertex.shader",
		"C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/fragment.shader");

	//Texture texture("C:/Users/1voic/source/repos/OpenGLRenderer/res/textures/Portal-Transparent-PNG.png");
	//texture.bind();
	//shader.set_uniform("u_texture", 0);

	glm::mat4 projection = glm::perspective(103.f, (float)window_width / window_height, -1.f, 1.f);

	float start_angle = 1.f;
	float angle = 0.005f;
	glm::vec3 axis{ 0.f, 1.f, 0.f };
	float scale = 0.005f;
	glm::mat4 model = glm::rotate(glm::scale(glm::mat4(1.f), glm::vec3{ scale, scale, scale }), angle, axis);

	Camera cam({ 1.f, 1.f, 2.f });
	glm::mat4 mvp = projection * cam.transform() * model;

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	//glfwSetKeyCallback(window.get(), Camera::on_key);

	Renderer renderer;
	while (!glfwWindowShouldClose(window.get()))
	{	
		renderer.clear();

		shader.set_uniform("u_model_view_projection", mvp);
		Renderer::draw(va, ib, shader);

		if(angle < start_angle)
			model = glm::rotate(model, angle, axis);
		mvp = projection * cam.transform() * model;

		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	return 0;
}