#ifndef OPENGLUTILS_HPP
#define OPENGLUTILS_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
class OpenGLUtils{
	public:
	static GLuint createBuffer(int, const float*, GLenum);
	static GLuint createTexture(unsigned,unsigned,const float*);
	static GLuint createTexture(unsigned,unsigned,GLuint,GLuint);

	static GLuint createTexture3D(unsigned ,unsigned ,unsigned , const float* );
	static bool writePNG(const std::string&, const unsigned ,const unsigned, const std::vector<float>& );
 	static bool writePNG(const std::string&, const unsigned ,const unsigned, const float*);

	static bool loadPNG(const std::string&, unsigned, unsigned, std::vector<float>&);

};
#endif
