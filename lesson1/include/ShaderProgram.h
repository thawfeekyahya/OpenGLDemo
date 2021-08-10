#pragma once
#include <string>
#include "GL/glew.h"

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    enum ShaderType {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    bool loadShaders(const char* vsFilename, const char* fsFilename);
    void use();


private:
    std::string fileToString(const std::string* filename);
    void checkCompilerError(GLuint shader,ShaderType type);
};