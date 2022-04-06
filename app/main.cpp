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

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.02f, 0.02f, 0.02f, 0.0f);

	std::vector vertices_buffer{
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	
	/*VertexBuffer vb(vertices_buffer, GL_STATIC_DRAW);
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(3);
	layout.push<float>(2);*/

	//VertexArray va(vb, layout);
	////VertexArray va(VertexBuffer(vertices_buffer, GL_STATIC_DRAW), layout); ::vertex buffer can't be deleted
	//VertexArray light_source_va(vb, layout);

	std::vector<uint32_t> indices_buffer{0, 1, 2, 3, 4, 5,
																 6, 7, 8, 9,10,11,
																12,13,14,15,16,17,
																18,19,20,21,22,23,
																24,25,26,27,28,29,
																30,31,32,33,34,35}; 

	Mesh box_mesh(vertices_buffer.data(), vertices_buffer.size(), indices_buffer.data(), indices_buffer.size());
	Mesh light_mesh(vertices_buffer.data(), vertices_buffer.size(), indices_buffer.data(), indices_buffer.size());

	//IndexBuffer ib(indices_buffer, GL_STATIC_DRAW);


	glm::mat4 projection = glm::perspective(90.f, (float)window_width / window_height, 1.f, -1.f);

	Shader light_source_shader("C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/light_source_vertex.shader",
		"C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/light_source_fragment.shader");
	glm::vec4 initial_light_pos{ 0.0f, 0.0f, 0.0f, 1.0f };
	PointLight white_light{
		initial_light_pos,
		//glm::normalize(glm::vec4{0.f } - initial_light_pos),
		glm::vec3{ 1.0f, 1.0f, 1.0f },
		glm::vec3{ 0.15f },
		glm::vec3{ 0.6f },
		glm::vec3{ 1.0f },
		0.09f, 0.032f//,
		//glm::cos(glm::radians(50.0f)), glm::cos(glm::radians(60.0f))
	};
	glm::mat4 light_source_model_matrix{ glm::translate(glm::mat4{1.0f},{3.f,5.f,0.f}) * glm::scale(glm::mat4(1.f), glm::vec3{0.3f}) };
	white_light.pos() = light_source_model_matrix * white_light.pos();
	light_source_shader.bind();
	light_source_shader.set_uniform("u_color", white_light.color());
	light_source_shader.set_uniform("u_model_view_projection", projection);


	Shader shader("C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/vertex.shader",
		"C:/dev/src/opengl_renderer/OpenGLRenderer/res/shaders/fragment.shader");

	//Material default_crate{ Texture<GL_TEXTURE_2D>{"C:/dev/src/opengl_renderer/OpenGLRenderer/res/textures/container2.png"},
	//						Texture<GL_TEXTURE_2D>{"C:/dev/src/opengl_renderer/OpenGLRenderer/res/textures/container2_specular.png"}, 32 };
	box_mesh.add_material("C:/dev/src/opengl_renderer/OpenGLRenderer/res/textures/container2.png",
						  "C:/dev/src/opengl_renderer/OpenGLRenderer/res/textures/container2_specular.png", 32);

	shader.bind();
	shader.add_light(white_light);
	shader.set_uniform("u_n_lights", 1);
	shader.set_material(box_mesh.material());


	float current_angle = 0.f;
	float delta_angle = 0.00005;
	float r = 7.f;
	float cam_heigh = 3.5f;
	auto rotate_cam_pos = [&current_angle, delta_angle, r, cam_heigh]()
	{
		current_angle += delta_angle;
		return glm::vec3{ r * cos(current_angle), cam_heigh,  r * sin(current_angle) };
	};
	Camera cam({ 0.f, 6.5f, -r });

	float scale = 2.f;
	auto make_model = [scale](const glm::vec3& pos) 
	{return glm::scale(glm::translate(glm::mat4(1.f),pos), glm::vec3{ scale, scale, scale }); };

	std::array cube_positions =
	{ glm::vec3(-2.f, -5.f, 5.f),
		glm::vec3(-4.f, 1.f, -3.f),
		glm::vec3(2.5f, -2.25f, -1.f),
		glm::vec3(0.f)
	};

	Renderer renderer;
	while (!glfwWindowShouldClose(window.get()))
	{
		cam.move_to(rotate_cam_pos());

		//light_source_model_matrix = glm::rotate(glm::mat4(1.0f), delta_angle * 5, {1.f,0.f, 0.f}) * light_source_model_matrix;
		//white_light.pos() = light_source_model_matrix * initial_light_pos;
		//white_light.direction() = glm::normalize(glm::vec3{ 0.0f } - glm::vec3{ white_light.pos() });

		//shader.bind();
		//shader.set_uniform("u_lights[0].pos",  white_light.pos());
		//shader.set_uniform("u_lights[0].direction", white_light.direction());
		box_mesh.bind();
		shader.bind();
		for (const auto& pos : cube_positions)
		{
			shader.set_uniform("u_model", make_model(pos));
			shader.set_uniform("u_view", cam.transform());
			shader.set_uniform("u_projection", projection);
			//Renderer::draw(va, ib, shader);
			renderer.draw(box_mesh, shader);
		}	

		light_source_shader.bind();
		light_source_shader.set_uniform("u_model_view_projection", projection * cam.transform() * light_source_model_matrix);
		renderer.draw(light_mesh, light_source_shader);
		//renderer.draw(light_source_va, ib, light_source_shader);
		glfwSwapBuffers(window.get());
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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