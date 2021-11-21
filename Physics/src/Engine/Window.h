#pragma once

struct GLFWwindow;

class Window
{
public:
	~Window() {}
	void HideMouse(bool bHide);

	static Window* getInstance();
	GLFWwindow* setWindow(GLFWwindow* _window){window = _window;}
	GLFWwindow* getWindow(){return window;}
private:
	GLFWwindow* window;
	Window();
	static Window* instance;
};