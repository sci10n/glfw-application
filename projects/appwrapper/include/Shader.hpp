#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//==================================================================
// Specify a Shader given a source file-path and a GL_*_SHADER type.
//==================================================================
class Shader{
private:
	GLuint _shaderID;
	std::string readFile(const std::string&) const;

public:
	~Shader();
	Shader() = delete;
	Shader(const GLuint&);

	Shader(const Shader&) = default;
	Shader& operator=(const Shader&) = default;

	Shader(Shader&&) = default;
	Shader& operator=(Shader&&) = default;

	bool fromFile(const std::string&);
	bool fromString(const char*);

	bool compile();
	GLuint getID() const;
};

#endif