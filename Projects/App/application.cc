#if defined _WIN32
	#include <Windows.h>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.hpp"
#include "ShaderProgram.hpp"
#include "SpriteBatch.hpp"
#include "Sprite.hpp"
#include "OrthographicCamera.hpp"
#include "Texture.hpp"
#include "OpenGLUtils.hpp"
#include <iostream>

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	Application* application = new Application(WIDTH, HEIGHT, "Application FPS @ ");
	application->init();
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a orthographic camera and set viewport to local coordinates scaled to 32x32 textures.
	OrthographicCamera* camera = new OrthographicCamera(WIDTH/32.0f, HEIGHT/32.0f, false);

	std::vector<float> textureData; 
	OpenGLUtils::loadPNG("assets/texture2.png",32,32,textureData);

	Texture testTexture (32,32,&textureData[0]);

	SpriteBatch *batch = new SpriteBatch();

	while (!application->isRunning())
	{
		Sprite sprite(testTexture, { 0, 0 }, { 2, 2 });
		application->tick();
		camera->update();
		glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		batch->begin(camera->combined(), true);
		batch->draw(sprite);
		batch->end();
		glBindVertexArray(0);
	}

	delete application;
	application = nullptr;

	return 0;
}