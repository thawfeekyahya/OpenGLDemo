#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class SimpleShader {
private:
   void checkForError(GLuint& pShader,GLint& status);

// Data in CPU memory
//location = 0,  is the same id represent in vertexAttribPointer
const GLchar* vertex1 = R"END(
   #version 330 core
   layout (location = 0) in vec3 pos;
   void main()
   {
   gl_Position = vec4(pos.x,pos.y,pos.z,1.0);
   }
)END";

const GLchar* fragment1 = R"END(
   #version 330 core 
   out vec4 frag_color;
   void main()
   {
   frag_color = vec4(0.35f,0.96f,0.3f,1.0f);
   }
)END";

public :
   SimpleShader();
   const GLchar** getVertexShader(int id=0);
   const GLchar** getFragmentShader(int id=0);
   void drawTriangle(GLuint* bufferObject);
   void enableActiveVertexArrayObj(GLuint* obj);
   void createVertexShader(GLuint& pShader);
   void createFragmentShader(GLuint& pShader);
   void linkShaders(GLuint& shaderProgram,GLuint& vertexShader,GLuint& fragmentShader);
   
};














