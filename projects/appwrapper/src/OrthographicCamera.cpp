#include "OrthographicCamera.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include <iostream>
OrthographicCamera::OrthographicCamera(float width, float height, bool yDown): _width{width}, _height{height} {
	_position = glm::vec3(0.0f,0.0f,0.0f);
	_forward = glm::vec3(0.0f,0.0f,1.0f);
	_up = glm::vec3(0.0f,-1.0f,0.0f);
	_zoom = 1.0f;
	_aspect = _width / _height;
}

void OrthographicCamera::setViewportSize(unsigned width, unsigned height){
	_width = width;
	_height = height;
}

void OrthographicCamera::update() {

	float minx = -_width / 2.0f * _zoom;
	float maxx =  _width / 2.0f * _zoom;
	float miny = -_height / 2.0f* _zoom;
	float maxy =  _height / 2.0f * _zoom;

	_projection = glm::ortho(minx, maxx, miny, maxy, 0.0f, 100.0f);
	_view = glm::lookAt(_position, _position + _forward, _up);
}

void OrthographicCamera::translate(const glm::vec3& translation){
	_position += translation;
}

void OrthographicCamera::zoomLevel(float zoomLevel){
	_zoom = zoomLevel;
}

glm::mat4 OrthographicCamera::projection() const {
	return _projection;
}

glm::mat4 OrthographicCamera::view() const {
	return _view;
}

glm::mat4 OrthographicCamera::combined() const {
	return _projection * _view;
}
