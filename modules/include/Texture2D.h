#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>


class Texture2D {
public:
    Texture2D();
    ~Texture2D();
    void loadTexture(const std::string& filename, bool genericMipMaps = true);
    void bind(GLuint textUint=0);

private:
   GLuint* mTexture;

};


