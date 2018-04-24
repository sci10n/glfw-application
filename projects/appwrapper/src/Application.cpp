#include "Application.hpp"
#include <iostream>
#include "stringPatch.hpp"

Application::Application(const unsigned width, const unsigned height, const std::string& title)
: _width{width}, _height{height}, _title{title}
{}

Application::~Application() {
	// Exit was ok!
    glfwTerminate();
}

int Application::init() {
	//====================================
    //  Init for GLFW
    //====================================
    const int MAJOR_VERSION = 3;
    const int MINOR_VERSION = 1;
    std::cout << "Starting GLFW context, OpenGL "<< MAJOR_VERSION << "." << MINOR_VERSION << std::endl;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(0); // Vsync.

    // Set input locators
    GLFWInputLocator* input = new GLFWInputLocator();
    glfwSetCursorPosCallback(_window, GLFWInputLocator::cursor_callback);
    glfwSetMouseButtonCallback(_window, GLFWInputLocator::mouse_callback);
    glfwSetKeyCallback(_window, GLFWInputLocator::keyboard_callback);
    Locator::setInput(input);

    //====================================
    //  Init for GLEW
    //====================================
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

      // Keep track of slowdown/speedup.
    _currentTime = glfwGetTime();
    _lastFrame = 0.0f;
    _deltaTime = 0.0f;
    _accumulatedTime = 0.0f;

    // For counting the framerate.
    _accumulatedFrames = 0;
    _frameAccumulatedTime = 0.0;
    return 0;
}

void Application::tick() {

 	_currentTime = glfwGetTime();
    _deltaTime = _currentTime - _lastFrame;
    _lastFrame = _currentTime;
    _accumulatedTime += _deltaTime;
    _accumulatedFrames += 1;
    // We accumulate the number of frames every second and print out this
    // number. This is better since we don't update the title every frame
    // and produces more stable results. Just resets counter and repeats.
	if (_currentTime - _frameAccumulatedTime >= 1.0) {
		const std::string fpsString = patch::to_string(_accumulatedFrames);
		const std::string windowTitle = _title + fpsString + " fps";
		glfwSetWindowTitle(_window, windowTitle.c_str());
		_frameAccumulatedTime = _currentTime;
        _accumulatedFrames = 0;
    }

	// Polling loop.
	glfwPollEvents();
    // Swap the render buffer to display
    glfwSwapBuffers(_window);
}

bool Application::isRunning() const {
	return glfwWindowShouldClose(_window);
}

void Application::setWidth(const unsigned width) {
	_width = width;
}

void Application::setHeight(const unsigned height) {
	_height = height;
}

void Application::setTitle(const std::string& title) {
	_title = title;
}

unsigned Application::getWidth() const {
	return _width;
}

unsigned Application::getHeight() const {
	return _height;
}

std::string Application::getTitle() const {
	return _title;
}