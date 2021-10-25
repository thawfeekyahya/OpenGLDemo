#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "SimpleShader.h"

//-----------------Global Properites

GLFWwindow* pWindow = NULL;


const GLchar* vertexShaderSrc = R"END(
  #version 330 core
  layout (location = 0) in vec3 pos;
  void main()
  {
  gl_Position = vec4(pos.x,pos.y,pos.z,1.0);
  }
)END";

const GLchar* fragmentShaderSrc = R"END(
#version 330 core 
out vec4 frag_color;
void main()
{
 frag_color = vec4(0.35f,0.96f,0.3f,1.0f);
}
)END";



int main() {

  MainWindow openglWindow;
  SimpleShader simple;

  pWindow = openglWindow.initOpenGL();

  if (!pWindow) {
    std::cerr << " GLFW intialization failed"<<std::endl;
    return -1;
  }

  GLuint vertexObj,arrayObj;
  
  simple.drawTriangle(&vertexObj);
  simple.enableActiveVertexArrayObj(&arrayObj);
  

  
  
  //2 Tirangles in one 
  GLfloat vertices[] = {
    // pos1 pos1 pos3 is x y and z and pos4 pos5 pos6 is RGB
    -0.5f,  0.5f,  0.0f, 
     0.5f,  0.5f,  0.0f, 
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
  };

  GLuint indices [] = {
    0, 1, 2,
    0, 2, 3
  };

  GLuint vbo,vao,ibo; //vertex buffer object
  
  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

 
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Position Attribute
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
  glEnableVertexAttribArray(0);

  glGenBuffers(1,&ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

  //Color Attribute
  // glBindBuffer(GL_ARRAY_BUFFER,vbo2);
  // glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);
  // glEnableVertexAttribArray(1);


  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs,1,&vertexShaderSrc,NULL);
  glCompileShader(vs);

  GLint results;
  GLchar infoLog[512];

  glGetShaderiv(vs,GL_COMPILE_STATUS, &results);
  if(!results) {
    glGetShaderInfoLog(vs,sizeof(infoLog),NULL,infoLog);
    std::cout<<" Error! Vertex sharder failed to compile"<<infoLog<<std::endl;
  }


  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs,1,&fragmentShaderSrc,NULL);
  glCompileShader(fs);

   glGetShaderiv(fs,GL_COMPILE_STATUS, &results);
  if(!results) {
    glGetShaderInfoLog(vs,sizeof(infoLog),NULL,infoLog);
    std::cout<<" Error! Fragment sharder failed to compile"<<infoLog<<std::endl;
  }


  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,vs);
  glAttachShader(shaderProgram,fs);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram,GL_LINK_STATUS,&results);
  if(!results) {
    glGetProgramInfoLog(shaderProgram,sizeof(infoLog),NULL,infoLog);
    std::cout<< "Error! Shader Program linker failure" <<infoLog<<std::endl;
  }

  glDeleteShader(vs);
  glDeleteShader(fs);



  //Main Loop

   while (!glfwWindowShouldClose(pWindow)) {
    openglWindow.showFPS();
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(arrayObj);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);

    //glUseProgram(shaderProgram);

    //glBindVertexArray(vao);
    //glDrawArrays(GL_TRIANGLES,0,6);
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    //glBindVertexArray(0);

    glfwSwapBuffers(pWindow);
  }

  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1,&vao);
  glDeleteBuffers(1,&vbo);
  glDeleteBuffers(1,&ibo);

  glfwTerminate();
  return 0;
	
}


