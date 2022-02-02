#include <iostream>
#include <util.h>

int main()
{
	glfwInitialiser::getInstance();

	glfwWindowHandle window{ glfwInitialiser::createWindow(1280, 720, "Renderer") };
	if (!window.get())
		std::cout << "window creation error" << std::endl;

	glfwMakeContextCurrent(window.get());
	while (!glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.get());

		glfwPollEvents();
	}


	return 0;
}