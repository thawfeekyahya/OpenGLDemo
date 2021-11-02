#include "Texture2D.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  //Image utility tool // single header library
#include <string>
#include <iostream>


Texture2D::Texture2D(): 
    mTexture(0) 
{

}


Texture2D::~Texture2D() {

}

bool Texture2D::loadTexture(const std::string& filename, bool generateMipMaps) 
{
    int width,height, components;

    unsigned  char* imageData = stbi_load(filename.c_str(),&width,&height,&components,STBI_rgb_alpha);

    if(!imageData) {
        std::cerr<< "Error loading texture " << filename;
        return false;
    }


    glGenTextures(1,&mTexture);
    glBindTexture(GL_TEXTURE_2D,mTexture); // Make this as active in OpenGL state macine

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);

    if(generateMipMaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D,0);


    stbi_image_free(imageData);

    


   //mim map is the pre formated image with different sized t
    /**
     * GL_TEXTURE_2D -> type
     * 0             -> minMapEnabled ?
     * */
   // glTexImage2D(GL_TEXTURE_2D,0,);

    return true;

}

void Texture2D::bind(GLuint textUint) 
{
    glBindTexture(GL_TEXTURE_2D,mTexture);
}
