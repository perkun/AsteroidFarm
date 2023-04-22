#include "Window.h"

Window::Window(int w, int h, string title, bool fullscreen, bool visible)
{
	if (!glfwInit())
	{
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		exit(0);
	}
	width = w;
	height = h;
	this->title = title;


	glfwWindowHint(GLFW_SAMPLES, 4);

	// create window
	if (visible)
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	else
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	if (fullscreen)
		winptr = glfwCreateWindow(w, h, title.c_str(), glfwGetPrimaryMonitor(), NULL);
	else
		winptr = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

	glfwMakeContextCurrent(winptr);

	// user pointer
	glfwSetWindowUserPointer(winptr, this);
}



Window::~Window()
{
	destroy();
	glfwTerminate();
}




void Window::close()
{
	glfwSetWindowShouldClose(winptr, GLFW_TRUE);
}

void Window::destroy()
{
	glfwDestroyWindow(winptr);
}

