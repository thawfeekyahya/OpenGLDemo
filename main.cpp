#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "SimpleShader.h"

//-----------------Global Properites

GLFWwindow* pWindow = NULL;
void createShader(SimpleShader& simpleShader,GLuint& vertexShader,GLuint& fragmentShader,GLuint& shaderProgram);


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
  
 
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint shaderProgram = glCreateProgram();

  simple.createVertexShader(vertexShader);
  simple.createFragmentShader(fragmentShader);
  
  simple.linkShaders(shaderProgram,vertexShader,fragmentShader);

  //Main Loop

   while (!glfwWindowShouldClose(pWindow)) {
    openglWindow.showFPS();
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
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
  glDeleteVertexArrays(1,&arrayObj);
  glDeleteBuffers(1,&vertexObj);
  //glDeleteBuffers(1,&ibo);

  glfwTerminate();
  return 0;
	
}

