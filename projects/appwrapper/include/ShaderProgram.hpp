#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include <GL/glew.h>
#include "Shader.hpp"
#include <glm\glm.hpp>
//===========================================================================
// Manages shaders akin to typical Shader Programs such as the one in LibGDX
// Tries to not limit to only fragment and vertex shaders
//===========================================================================
class ShaderProgram{
private:
	GLuint _programId;

	const char* _defaultFrag =
		"#version 330 core\n"
		"\n"
		"in vec2 UV;\n"
		"in vec4 fragmentColor;\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"uniform sampler2D myTextureSampler;\n"
		"\n"
		"void main(){\n"
		"  color = texture( myTextureSampler, UV).rgba * fragmentColor;\n"
		"}\n";

	const char* _defaultVert =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
		"layout(location = 1) in vec4 vertexColor;\n"
		"layout(location = 2) in vec2 vertexTexture;\n"
		"\n"
		"out vec4 fragmentColor;\n"
		"out vec2 UV;\n"
		"\n"
		"uniform mat4 combined;\n"
		"\n"
		"\n"
		"void main(){\n"
		"	mat4 translationMatrix = mat4(1);\n"
		"   mat4 rotationMatrix = mat4(1);\n"
		"   mat4 scaleMatrix = mat4(1);\n"
		"\n"
		"    translationMatrix[3][0] = vertexPosition_modelspace.x;\n"
		"    translationMatrix[3][1] = vertexPosition_modelspace.y;\n"
		"    translationMatrix[3][2] = vertexPosition_modelspace.z;\n"
		"\n"
		"    // // Scale, rotate and then translate.\n"
		"    // // The order is important\n"
		"    mat4 model = translationMatrix * rotationMatrix * scaleMatrix;\n"
		"\n"
		"    gl_Position  = combined * model * vec4(1);\n"
		"    fragmentColor = vertexColor;\n"
		"    UV = vertexTexture;\n"
		"}\n";
public:
	~ShaderProgram();
	ShaderProgram(bool = true);

	ShaderProgram(const ShaderProgram&) = default;
	ShaderProgram& operator=(const ShaderProgram&) = default;

	ShaderProgram(ShaderProgram&&) = default;
	ShaderProgram& operator=(ShaderProgram&&) = default;

	void attach(const Shader&);
	bool link();
	void begin(const glm::mat4& combined);
	void end();
	GLuint getId() const;
};
#endif