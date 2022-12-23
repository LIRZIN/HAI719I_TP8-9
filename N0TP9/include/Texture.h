#ifndef TEXTURE_H_DEFINED
#define TEXTURE_H_DEFINED

#include <string>
#include <iostream>
#include <vector>
#include <GL/glew.h>

unsigned int loadCubemap( std::vector<std::string> faces );

GLuint loadTexture2DFromFilePath(const std::string& path);

void setDefaultTexture2DParameters(GLuint texture);

#endif
