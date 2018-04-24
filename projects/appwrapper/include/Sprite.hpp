#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.hpp"

class Sprite{
private:
	// Texture
	const Texture& _texture;
	// Centre
	glm::vec2 _position;
	// Size
	glm::vec2 _dimension;
	// Scale
	glm::vec2 _scale;
	// Tint
	glm::vec4 _color;
	// Centre of rotation
	glm::vec2 _origin;
	// Rotation angle in radiants
	float _angle;
	
public:
	// Texture, Position, dimension, scale, color, origin, rotation
	Sprite(const Texture&, const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec4&, const glm::vec2&, float);
	// Texture, Position, dimension, scale, color, origin
	Sprite(const Texture&, const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec4&, const glm::vec2&);
	// Texture, Position, dimension, scale, color
	Sprite(const Texture&, const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec4&);
	// Texture, Position, dimension, scale
	Sprite(const Texture&, const glm::vec2&, const glm::vec2&, const glm::vec2&);
	// Texture, Position, dimension
	Sprite(const Texture&, const glm::vec2&, const glm::vec2&);

	const Texture& getTexture() const;
	glm::vec2 getPosition() const;	
	glm::vec2 getDimension() const;
	glm::vec2 getScale() const;
	glm::vec4 getColor() const;
	glm::vec2 getOrigin() const;
	float getRotation() const;

	glm::vec2& position();
	glm::vec2& dimension();
	glm::vec2& scale();
	glm::vec4& color();
	glm::vec2& origin();

	float& rotation();
};
#endif