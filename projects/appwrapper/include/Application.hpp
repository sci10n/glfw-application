#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#if defined _WIN32
	#include <windows.h>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Locator.hpp"

class Application {
private:
	unsigned _width;
	unsigned _height;
	std::string _title;
	GLFWInputLocator* _input;
	GLFWwindow* _window;
	float _currentTime;
    float _lastFrame;
    float _deltaTime;
    float _accumulatedTime;
    unsigned _accumulatedFrames;
    float _frameAccumulatedTime;

public:	
	Application(const unsigned width, const unsigned height, const std::string& title);
	~Application();
	int init();
	void tick();

	bool isRunning() const;
	void setWidth(const unsigned width);
	void setHeight(const unsigned height);
	void setTitle(const std::string& title);

	unsigned getWidth() const;
	unsigned getHeight() const;
	std::string getTitle() const;

};
#endif