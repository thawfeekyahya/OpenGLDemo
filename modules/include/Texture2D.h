#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>


class Texture2D {
public:
    Texture2D();
    ~Texture2D();
    bool loadTexture(const std::string& filename, bool generateMipMaps = true);
    void bind(GLuint textUint=0);

private:
   GLuint mTexture;
};


