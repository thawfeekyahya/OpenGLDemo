#pragma once
#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"

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

    //void setUniform(const GLchar* name,const glm::vect2& v )


private:
    std::string fileToString(const std::string& filename);
    void checkCompilerError(GLuint shader,ShaderType type);

    GLuint mHandle;
};
