#include "ShaderProgram.hpp"
#include <iostream>
#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

ShaderProgram::~ShaderProgram(){
	glDeleteProgram(_programId);
	_programId = 0;
}

ShaderProgram::ShaderProgram(bool useDefaultShader){
	_programId = glCreateProgram();
	if (useDefaultShader){
		std::cout << "Using default shaders" << std::endl;
		Shader fragmentShader(GL_FRAGMENT_SHADER);
		fragmentShader.fromString(_defaultFrag);

		Shader vertexShader(GL_VERTEX_SHADER);
		vertexShader.fromString(_defaultVert);

		attach(fragmentShader);
		attach(vertexShader);
	}
}

void ShaderProgram::attach(const Shader& shader){
	glAttachShader(_programId, shader.getID());
	link();
}

bool ShaderProgram::link(){
	glLinkProgram(_programId);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(_programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

void ShaderProgram::begin(const glm::mat4& combined){
	glUseProgram(_programId);
	GLuint viewId = glGetUniformLocation(_programId, "combined");
	glUniformMatrix4fv(viewId, 1, GL_FALSE, &(combined[0][0]));
}

void ShaderProgram::end(){
	glUseProgram(0);
}

GLuint ShaderProgram::getId() const{
	return _programId;
}

