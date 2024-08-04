
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "debug.h"
#include <iostream>

using namespace std;

Debug::Debug() {

}


void Debug::debug_program(GLuint program) {
   int max_length = 2048;
   int actual_length = 0;
   char log[1024];
   
   int params = -1;
   
   glGetProgramiv(program,GL_LINK_STATUS,&params);
   if (GL_TRUE != params) {
   	cerr<< "ERROR could not link the program "<<program<<endl;
   	glGetProgramInfoLog(program,max_length,&actual_length,log);
   	printf("shader info log for GL index %u:\n%s\n",program,log);
   }
}

void Debug::debug_shader(GLuint shaderIndex) {
    int max_length = 2048;
    int actual_length = 0;

    char log[1024];
    
    int params = -1;
    
    glGetShaderiv(shaderIndex,GL_COMPILE_STATUS,&params);
    
    if (GL_TRUE != params) {
        cerr<<"GL Shader index "<<shaderIndex<<" did not compile"<<endl;
        
        glGetShaderInfoLog(shaderIndex,max_length,&actual_length,log);
        printf("shader info log for GL index %u:\n%s\n",shaderIndex,log);
    }

}
