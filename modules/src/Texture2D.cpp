#include "Texture2D.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <string>


Texture2D::Texture2D(): 
    mTexture(0) 
{

}


Texture2D::~Texture2D() {

}

void Texture2D::loadTexture(const std::string& filename, bool genericMipMaps) 
{
    int width,height, component;

}

void Texture2D::bind(GLuint textUint) 
{
    
}
