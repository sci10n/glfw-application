#include "OpenGLUtils.hpp"
#include <GL/glew.h>

#include "foreign/lodepng.h"
#include <iostream>
#include <sstream>

GLuint OpenGLUtils::createBuffer(int size, const float* data, GLenum usage)
{
    GLuint ret_val = 0;
    glGenBuffers(1,&ret_val);
    glBindBuffer(GL_ARRAY_BUFFER,ret_val);
    glBufferData(GL_ARRAY_BUFFER,size*sizeof(float),data,usage);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    return ret_val;
}

GLuint OpenGLUtils::createTexture(unsigned width,unsigned height, GLuint type, GLuint format){
  GLuint ret_val = 0;
    glGenTextures(1,&ret_val);
    glBindTexture(GL_TEXTURE_2D,ret_val);
    glTexImage2D(GL_TEXTURE_2D,0,type,width,height,0,type,format,0);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    return ret_val;
}

GLuint OpenGLUtils::createTexture(unsigned width,unsigned height, const float* data ){
 	GLuint ret_val = 0;
    glGenTextures(1,&ret_val);
    glBindTexture(GL_TEXTURE_2D,ret_val);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_FLOAT,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    return ret_val;
}

GLuint OpenGLUtils::createTexture3D(unsigned width,unsigned height,unsigned depth, const float* data ){
  GLuint ret_val = 0;
    glGenTextures(1,&ret_val);
    glBindTexture(GL_TEXTURE_3D,ret_val);
    glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA,width,height,depth,0,GL_RGBA,GL_FLOAT,data);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    return ret_val;
}

// Assumes RGB values interleaved in the data vector on the form 0.0f - 1.0f for each channel 
bool OpenGLUtils::writePNG(const std::string& filePath, const unsigned width, const unsigned height, const std::vector<float>& data){
    std::vector<unsigned char> image;
    for(unsigned i = 0; i < width*height; i++){
      //std::cout << data.at(i*4 + 0) << " " << data.at(i*4 + 1) << " " << data.at(i*4 + 2) << " " << data.at(i*4 + 3) << " "; 
      image.push_back((unsigned char)(data.at(i*4 + 0)*255));
      image.push_back((unsigned char)(data.at(i*4 + 1)*255));
      image.push_back((unsigned char)(data.at(i*4 + 2)*255));
      image.push_back((unsigned char)(data.at(i*4 + 3)*255));
    }

   //Encode the image
  unsigned error = lodepng::encode(filePath, image, width, height);
  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
   return true;
}

bool OpenGLUtils::loadPNG(const std::string& filePath, unsigned width, unsigned height, std::vector<float>& data){

  std::vector<unsigned char> image; //the raw pixels
  int error = lodepng::decode(image, width, height, filePath);
  data.resize(width*height*4,0.0f);
  //if there's an error, display it
  if(error){
  	std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  	return false;
  } 

  for(unsigned i = 0 ; i < width*height*4; i++){
  	data[i] = ((float)image[i]/255.0f);
  }
  return true;
}
