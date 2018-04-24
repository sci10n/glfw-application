#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class OrthographicCamera {
	
	private:
		float _width;
		float _height;
		float _zoom;
		float _aspect;
		glm::vec3 _position;
		glm::vec3 _forward;
		glm::vec3 _up;
		glm::mat4 _projection;
		glm::mat4 _view;
	public:
		OrthographicCamera(float width, float height, bool yDown);
		void setViewportSize(unsigned, unsigned);
		void update();
		void translate(const glm::vec3&);
		void zoomLevel(float);

		glm::mat4 projection() const;
		glm::mat4 view() const;
		glm::mat4 combined() const;
};

#endif