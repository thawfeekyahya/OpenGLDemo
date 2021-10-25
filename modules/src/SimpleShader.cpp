#include "SimpleShader.h"
#include <iostream>

SimpleShader::SimpleShader(){}


//Moving this to cpp ,coz of flexlible array issue
GLfloat triangleVertices[] = {
    // pos1 pos1 pos3 is x y and z and pos4 pos5 pos6 is RGB
    -0.5f,  0.5f,  0.0f, 
     0.5f,  0.5f,  0.0f, 
     0.5f, -0.5f,  0.0f,
};


 const GLchar** SimpleShader::getVertexShader(int id) {

    switch(id) {
        case 0:
        return &vertex1;
        break;
    }
}

const GLchar** SimpleShader::getFragmentShader(int id) 
{
    switch(id) {
        case 0:
        return &fragment1;
        break;
    }
   
}


//This just draws the triangle and no coloring, simple put only points in space
void SimpleShader::drawTriangle(GLuint* bufferObject) 
{
  //Create new buffer in GPU memory
  glGenBuffers(1,bufferObject);  

  //Make bufferObject active of type GL_ARRAY_BUFFER
  glBindBuffer(GL_ARRAY_BUFFER,*bufferObject);

  //Take the CPU data ( traingleVertices ) and pass it to the active buffer (based on previous step)
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices),triangleVertices,GL_STATIC_DRAW);

}

void SimpleShader::enableActiveVertexArrayObj(GLuint* obj) 
{
  //This is required by core OpenGL
  int vertexId = 0;
  glGenVertexArrays(1,obj);
  glBindVertexArray(*obj);
  
  //VertexAttribPointer is used to describe how data is laid out in the vertex array 
  // <triangleVertices> is array of 9 elements ,but its actually represented as 3 vertex point of a triange
  /**
   * @vertexID unique id and this is referenced in the fragment shader code
   * @ 3 , how many data in a stride
   * @ GL_FLOAT type of data
   * @ GL_FALSE shoudl normalize 
   * @ 0 Offset start
   * @ NULL offset end
   * */
  glVertexAttribPointer(vertexId,3,GL_FLOAT,GL_FALSE,0,NULL);

  //enable this vertex array
  glEnableVertexAttribArray(vertexId); 
}


void SimpleShader::createVertexShader(GLuint& pShader) {
  glShaderSource(pShader,1,getVertexShader(0),0);
  glCompileShader(pShader);

  GLint vertexCompilationStatus; 
  glGetShaderiv(pShader,GL_COMPILE_STATUS,&vertexCompilationStatus);

  checkForError(pShader,vertexCompilationStatus);
}

void SimpleShader::createFragmentShader(GLuint& pShader) {
   //Fragment shader
  glShaderSource(pShader,1,getFragmentShader(0),0);
  glCompileShader(pShader);

  GLint fragmentCompilationStatus; 
  glGetShaderiv(pShader,GL_COMPILE_STATUS,&fragmentCompilationStatus);
  checkForError(pShader,fragmentCompilationStatus);
}

void SimpleShader::checkForError(GLuint& pShader,GLint& status) {
  if(status == GL_FALSE) {
    GLchar message[256];
    glGetShaderInfoLog(pShader,sizeof(message),0,&message[0]);
    std::cout<<message<<"-> Error creating shader program";
    exit(1);
  }
}

void SimpleShader::linkShaders(GLuint& shaderProgram,GLuint& vertexShader,GLuint& fragmentShader) {

  GLint status;

  glAttachShader(shaderProgram,vertexShader);
  glAttachShader(shaderProgram,fragmentShader); 
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram,GL_LINK_STATUS,&status);
  checkForError(shaderProgram,status);
  
  //Clean up after linking
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}

