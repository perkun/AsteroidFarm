#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>
#include <string>

using namespace std;

class GLFWwindow;

class Window
{
public:
	Window(int, int, string, bool, bool);
	~Window();

	void destroy();
	void close();

	GLFWwindow* winptr;
	int width, height;
	string title;
};

#endif /* WINDOW_H_ */
