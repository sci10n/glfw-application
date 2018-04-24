#include "SpriteBatch.hpp"
#include <iostream>

Batch::Batch(const Texture* texture): _texture{texture}, _batchedSprites{0} {
	_vertexBuffer = new GLfloat[MAX_BUFFERED_SPRITES * FLOATS_PER_SPRITE_VERTEX];
	_colorBuffer = new GLfloat[MAX_BUFFERED_SPRITES * FLOATS_PER_SPRITE_COLOR];
	_indicesBuffer = new GLuint[MAX_BUFFERED_SPRITES * 6];
	_uvBuffer = new GLubyte[MAX_BUFFERED_SPRITES * 8];
	_uploaded = false;
	//Allocate 2 Vertex buffer objects, one for verticies and one for texturecoords
	glGenBuffers(4, _vbo);

	// Set up indices for sprites
	GLuint j = 0;
	for(unsigned i = 0; i < MAX_BUFFERED_SPRITES * 6; i += 6){
		_indicesBuffer[i + 0] = (GLuint)(j + 0);
		_indicesBuffer[i + 1] = (GLuint)(j + 1);
		_indicesBuffer[i + 2] = (GLuint)(j + 2);
		_indicesBuffer[i + 3] = (GLuint)(j + 2);
		_indicesBuffer[i + 4] = (GLuint)(j + 3);
		_indicesBuffer[i + 5] = (GLuint)(j + 0);
		j += 4;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFERED_SPRITES * 6 * sizeof(GLuint), _indicesBuffer, GL_DYNAMIC_DRAW);
	

	//  inverted since OpenGL uses flipped coords
	for(unsigned i = 0; i < MAX_BUFFERED_SPRITES * 8; i += 8){
		_uvBuffer[i + 0] = (GLubyte)(0);
		_uvBuffer[i + 1] = (GLubyte)(0);
		_uvBuffer[i + 2] = (GLubyte)(0);
		_uvBuffer[i + 3] = (GLubyte)(1);
		_uvBuffer[i + 4] = (GLubyte)(1);
		_uvBuffer[i + 5] = (GLubyte)(1);
		_uvBuffer[i + 6] = (GLubyte)(1);
		_uvBuffer[i + 7] = (GLubyte)(0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFERED_SPRITES * 8 * sizeof(GLubyte), _uvBuffer, GL_DYNAMIC_DRAW);
	
}

Batch::~Batch(){
	// Delete GPU-allocated buffers
	glDeleteBuffers(4, _vbo);
	delete _vertexBuffer;
	delete _indicesBuffer;
	delete _colorBuffer;
	delete _uvBuffer;
}

void Batch::begin(bool clear) {
	_clear = clear;
	if(clear){
		_batchedSprites = 0;
		_uploaded = false;
	}
}

void Batch::draw(
	const glm::vec2& position, 
	const glm::vec2& dimensions,
	const glm::vec2& scale,
	const glm::vec4& color,
	const glm::vec2& origin,
	const float angle
) {
	if(_batchedSprites > MAX_BUFFERED_SPRITES){
		return;
	}

	glm::vec2 worldOrigin = position + origin;
	glm::vec2 f1 = -origin;
	glm::vec2 f2 = dimensions - origin;

	f1 *= scale;
	f2 *= scale;

	float cos_rot = cos(angle);
	float sin_rot = sin(angle);

	const GLfloat  x1 = cos_rot * f1.x - sin_rot * f1.y;
	const GLfloat  y1 = sin_rot * f1.x + cos_rot * f1.y;
	const GLfloat  z1 = 1.0f;

	const GLfloat  x2 = cos_rot * f1.x - sin_rot * f2.y;
	const GLfloat  y2 = sin_rot * f1.x + cos_rot * f2.y;
	const GLfloat  z2 = 1.0f;

	const GLfloat  x3 = cos_rot * f2.x - sin_rot * f2.y;
	const GLfloat  y3 = sin_rot * f2.x + cos_rot * f2.y;
	const GLfloat  z3 = 1.0f;

	const GLfloat  x4 = cos_rot * f2.x - sin_rot * f1.y;
	const GLfloat  y4 = sin_rot * f2.x + cos_rot * f1.y;
	const GLfloat  z4 = 1.0f;

	//std::cout << "(" << x1 + worldOrigin.x << "," << y1 + worldOrigin.y << "," << z1 << ")" <<  std::endl;
	//std::cout << "(" << x2 + worldOrigin.x << "," << y2 + worldOrigin.y << "," << z2 << ")" << std::endl;
	//std::cout << "(" << x3 + worldOrigin.x << "," << y3 + worldOrigin.y << "," << z3 << ")" << std::endl;
	//std::cout << "(" << x4 + worldOrigin.x << "," << y4 + worldOrigin.y << "," << z4 << ")" << std::endl;



	int index = _batchedSprites * FLOATS_PER_SPRITE_VERTEX;
	_vertexBuffer[index + 0] = x1 + worldOrigin.x;
	_vertexBuffer[index + 1] = y1 + worldOrigin.y;
	_vertexBuffer[index + 2] = z1;

	_vertexBuffer[index + 3] = x2 + worldOrigin.x;
	_vertexBuffer[index + 4] = y2 + worldOrigin.y;
	_vertexBuffer[index + 5] = z2;

	_vertexBuffer[index + 6] = x3 + worldOrigin.x;
	_vertexBuffer[index + 7] = y3 + worldOrigin.y;
	_vertexBuffer[index + 8] = z3;

	_vertexBuffer[index + 9]  = x4 + worldOrigin.x;
	_vertexBuffer[index + 10] = y4 + +worldOrigin.y;
	_vertexBuffer[index + 11] = z4;

	index = _batchedSprites * FLOATS_PER_SPRITE_COLOR;

	_colorBuffer[index + 0] = color.x;
	_colorBuffer[index + 1] = color.y;
	_colorBuffer[index + 2] = color.z;
	_colorBuffer[index + 3] = color.w;

	_colorBuffer[index + 4] = color.x;
	_colorBuffer[index + 5] = color.y;
	_colorBuffer[index + 6] = color.z;
	_colorBuffer[index + 7] = color.w;

	_colorBuffer[index + 8] = color.x;
	_colorBuffer[index + 9] = color.y;
	_colorBuffer[index + 10] = color.z;
	_colorBuffer[index + 11] = color.w;

	_colorBuffer[index + 12]  = color.x;
	_colorBuffer[index + 13] = color.y;
	_colorBuffer[index + 14] = color.z;
	_colorBuffer[index + 15] = color.w;

	++_batchedSprites;
}

void Batch::end() {	

	if(_texture)
		_texture->begin(0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	if(!_uploaded)
		glBufferData(GL_ARRAY_BUFFER, FLOATS_PER_SPRITE_VERTEX * _batchedSprites * sizeof(GLfloat), _vertexBuffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	if(!_uploaded)
		glBufferData(GL_ARRAY_BUFFER, FLOATS_PER_SPRITE_COLOR * _batchedSprites * sizeof(GLfloat), _colorBuffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[3]);
	if(!_uploaded)
		glBufferData(GL_ARRAY_BUFFER, 8 * _batchedSprites * sizeof(GLubyte), _uvBuffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 2, GL_UNSIGNED_BYTE , GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[2]);
	glDrawElements(GL_TRIANGLES, 6 * _batchedSprites * sizeof(GLuint), GL_UNSIGNED_INT,(void*)0);

	// Disable attribute
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if(_texture)
		_texture->end();
	_uploaded = true;
}

SpriteBatch::SpriteBatch(ShaderProgram* shaderProgram){
	// Allow to send external shader program. Otherwise will a default be used.
	if (shaderProgram) {
		_program = shaderProgram;
	}
	else {
		_program = new ShaderProgram();
	}
}

SpriteBatch::~SpriteBatch(){
	if(_batches.empty()){
		return;
	}

	for(auto it = _batches.begin(); it != _batches.end(); ++it){
		delete ((*it).second);
	}
	_batches.clear();

	delete _program;
	_program = nullptr;
}

void SpriteBatch::begin(const glm::mat4& combined, bool clear){
	// Start shader program
	_program->begin(combined);
	for(auto it = _batches.begin(); it != _batches.end(); ++it){
		(*it).second->begin(clear);
	}
}
void SpriteBatch::draw(const Texture* texture, const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& scale, const glm::vec4& color, const glm::vec2& origin, const float angle){
	Batch* batch = nullptr;
	try{
		if(texture)
			batch = _batches.at(texture->getID());
		else
			batch = _batches.at(-1);
	}
	catch(...){
		if(texture){
			_batches[texture->getID()] = new Batch(texture);
			batch = _batches.at(texture->getID());
			batch->begin(true);
		}
		else{
			_batches[-1] = new Batch(texture);
			batch = _batches.at(-1);
			batch->begin(true);
		}
	}
	batch->draw(position,dimension, scale, color, origin, angle);
}

void SpriteBatch::draw(const Sprite& sprite) {
	draw(&(sprite.getTexture()), sprite.getPosition(), sprite.getDimension(), sprite.getScale(), sprite.getColor(), sprite.getOrigin(), sprite.getRotation());
}

void SpriteBatch::end() {
	for(auto it = _batches.begin(); it != _batches.end(); ++it){
		(*it).second->end();
	}
	
	// End shader program
	_program->end();
}