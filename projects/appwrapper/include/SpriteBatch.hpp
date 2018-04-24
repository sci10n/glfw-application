#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP
#include <GL/glew.h>
#include "Texture.hpp"
#include "Sprite.hpp"
#include "ShaderProgram.hpp"
#include "OrthographicCamera.hpp"
#include <vector>
#include <map>

#define FLOATS_PER_SPRITE_VERTEX 12
#define FLOATS_PER_SPRITE_COLOR 16
#define MAX_BUFFERED_SPRITES 65536

class Batch {
private:
	GLuint _vertexArray;
	GLuint _vbo[4];
	GLfloat* _vertexBuffer;
	GLfloat* _colorBuffer;
	GLubyte* _uvBuffer;
	GLuint*  _indicesBuffer;

	const Texture* _texture;
	unsigned _batchedSprites;
	bool _clear;
	bool _uploaded;

public:
	Batch(const Texture*);
	~Batch();
	void begin(bool);
	void draw(const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec4&, const glm::vec2&, const float); 
	void end();
};

class SpriteBatch {
private:
	std::map<GLuint,Batch*> _batches;
	ShaderProgram* _program;
public:
	SpriteBatch(ShaderProgram* = nullptr);
	~SpriteBatch();

	void begin(const glm::mat4& combined, bool clear = true);
	void draw(const Texture*, const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec4&, const glm::vec2&, const float);
	void draw(const Sprite&);
	void end();
};
#endif