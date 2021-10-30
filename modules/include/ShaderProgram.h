#pragma once
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/vec2.hpp> 
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

    void setUniform(const GLchar* name,const glm::vec2& v);
    void setUniform(const GLchar* name,const glm::vec3& v);
    void setUniform(const GLchar* name,const glm::vec4& v);

private:
    std::string fileToString(const std::string& filename);
    void checkCompilerError(GLuint shader,ShaderType type);
    GLuint getUniformLocation(const GLchar* name);

    GLuint mHandle;
    std::map<std::string,GLint> mUniformLocations;
};
