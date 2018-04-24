#include "Sprite.hpp"

Sprite::Sprite(
	const Texture& texture,
	const glm::vec2& position,
	const glm::vec2& dimension,
	const glm::vec2& scale,
	const glm::vec4& color,
	const glm::vec2& origin,
	float angle)
	:
	_texture(texture),
	_position(position),
	_dimension(dimension),
	_scale(scale),
	_color(color),
	_origin(origin),
	_angle{ angle }
	{}

Sprite::Sprite(
	const Texture& texture,
	const glm::vec2& position,
	const glm::vec2& dimension,
	const glm::vec2& scale,
	const glm::vec4& color,
	const glm::vec2& origin)
	:
	_texture(texture),
	_position(position),
	_dimension(dimension),
	_scale(scale),
	_color(color),
	_origin(origin),
	_angle{ 0.0f }
{}

Sprite::Sprite(
	const Texture& texture,
	const glm::vec2& position,
	const glm::vec2& dimension,
	const glm::vec2& scale,
	const glm::vec4& color)
	:
	_texture(texture),
	_position(position),
	_dimension(dimension),
	_scale(scale),
	_color(color),
	_origin(_scale /2.0f),
	_angle{ 0.0f }
{}

Sprite::Sprite(
	const Texture& texture,
	const glm::vec2& position,
	const glm::vec2& dimension,
	const glm::vec2& scale)
	:
	_texture(texture),
	_position(position),
	_dimension(dimension),
	_scale(scale),
	_color(1.0f,1.0f,1.0f,1.0f),
	_origin(_scale / 2.0f),
	_angle{ 0.0f }
{}

Sprite::Sprite(
	const Texture& texture,
	const glm::vec2& position,
	const glm::vec2& dimension)
	:
	_texture(texture),
	_position(position),
	_dimension(dimension),
	_scale(1.0f,1.0f),
	_color(1.0f, 1.0f, 1.0f, 1.0f),
	_origin(_scale / 2.0f),
	_angle{ 0.0f }
{}

const Texture& Sprite::getTexture() const {
	return _texture;
}

glm::vec2 Sprite::getPosition() const {
	return _position;
}

glm::vec2 Sprite::getDimension() const {
	return _dimension;
}

glm::vec2 Sprite::getScale() const {
	return _scale;
}

glm::vec4 Sprite::getColor() const {
	return _color;
}

glm::vec2 Sprite::getOrigin() const {
	return _origin;
}

float Sprite::getRotation() const {
	return _angle;
}

glm::vec2& Sprite::position() {
	return _position;
}

glm::vec2& Sprite::dimension() {
	return _dimension;
}

glm::vec2& Sprite::scale() {
	return _scale;
}

glm::vec4& Sprite::color() {
	return _color;
}

glm::vec2& Sprite::origin() {
	return _origin;
}

float& Sprite::rotation() {
	return _angle;
}
