#include <iostream>
#include <GL/glew.h>
#include <util.h>
#include <stdint.h>

#include "Bresenham.h"

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

	//float vertices_buffer[] = {
	//	0.5f, 0.5f,
	//	0.0f, 0.0f,
	//	-0.5f, 0.5f
	//};
	//uint32_t vertices;
	//glGenBuffers(1, &vertices);
	//glBindBuffer(GL_ARRAY_BUFFER, vertices);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices_buffer, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0 );
	//glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		drawLine(100, 100, 200, 200, window);



		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}

	return 0;
}