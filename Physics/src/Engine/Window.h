#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

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