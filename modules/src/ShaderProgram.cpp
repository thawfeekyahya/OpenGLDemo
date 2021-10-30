#include "ShaderProgram.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <sstream>



ShaderProgram::ShaderProgram():mHandle(0) {

}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(mHandle);
}


bool ShaderProgram::loadShaders(const char* vsFilename, const char* fsFilename) {

    std::string vertexShaderString = fileToString(vsFilename);
    std::string fragmentShaderString = fileToString(fsFilename);

    const GLchar* vsSourcePtr = vertexShaderString.c_str();
    const GLchar* fsSourcePtr = fragmentShaderString.c_str();


    GLuint vertexShader =   glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader,1,&vsSourcePtr,NULL);
    glShaderSource(fragmentShader,1,&fsSourcePtr,NULL);

    glCompileShader(vertexShader);
    checkCompilerError(vertexShader,VERTEX);

    glCompileShader(fragmentShader);
    checkCompilerError(fragmentShader,FRAGMENT);

    mHandle = glCreateProgram();
    glAttachShader(mHandle,vertexShader);
    glAttachShader(mHandle,fragmentShader);
    glLinkProgram(mHandle);

    checkCompilerError(mHandle,ShaderType::PROGRAM);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
  
}

void ShaderProgram::use(){
    if(mHandle > 0 ) {
        glUseProgram(mHandle);
    }
}

// void ShaderProgram::setUniform(const GLchar* name,const glm::vect2& v ){

// }

std::string ShaderProgram::fileToString(const std::string& filename) {
    std::stringstream stringStream;
    std::ifstream  file;

    try {
        file.open(filename,std::ios::in);

        if(!file.fail()) {
            stringStream << file.rdbuf();
        }

        file.close();

    }catch(std::exception ex) {
        std::cerr<<"Error reading shader file name "<<std::endl;
    }

    return stringStream.str();

}
void ShaderProgram::checkCompilerError(GLuint shader,ShaderType type) {

    int status = 0;

    switch(type) {
        case ShaderType::VERTEX:
        case ShaderType::FRAGMENT:
            glGetShaderiv(shader,GL_COMPILE_STATUS,&status);

            if(status == GL_FALSE) {
                GLint length=0;
                glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&length);
                
                std::string errorLog(length,' ');

                glGetShaderInfoLog(shader,length,&length,&errorLog[0]);

                std::cerr<< "Error Shader failed to compile"<<errorLog<<std::endl;
            }
        
        break;
        case ShaderType::PROGRAM:
            glGetProgramiv(mHandle,GL_LINK_STATUS,&status);

            if(status == GL_FALSE) {
                GLint length=0;
                glGetProgramiv(mHandle,GL_INFO_LOG_LENGTH,&length);
                
                std::string errorLog(length,' ');

                glGetProgramInfoLog(mHandle,length,&length,&errorLog[0]);

                std::cerr<< "Error Program failed to link"<<errorLog<<std::endl;
            }

        break;
    }

}