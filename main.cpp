#include <iostream>
#include <sstream>

#include "stb_image.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "SimpleShader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

//-----------------Global Properites

GLFWwindow* pWindow = NULL;
void createShader(SimpleShader& simpleShader,GLuint& vertexShader,GLuint& fragmentShader,GLuint& shaderProgram);


int main() {

  MainWindow openglWindow;
  SimpleShader simple;
  ShaderProgram customShader;

  pWindow = openglWindow.initOpenGL();

  if (!pWindow) {
    std::cerr << " GLFW intialization failed"<<std::endl;
    return -1;
  }

  GLuint vertexObj,arrayObj;
  
  GLuint indexObj; // To draw quad // avoid redrawing same index
  
  simple.createBufferInGPU(&vertexObj);
  simple.mapDataToGPU(&arrayObj);
  simple.createIndicesBuffer(&indexObj);



  /*
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint shaderProgram = glCreateProgram();

  simple.createVertexShader(vertexShader);
  simple.createFragmentShader(fragmentShader);
  
  simple.linkShaders(shaderProgram,vertexShader,fragmentShader);
  */

  customShader.loadShaders("basic.vert","basic.frag");

  Texture2D texture;
  const std::string imageName="benz.png";
  texture.loadTexture(imageName,true);


  //Main Loop

   while (!glfwWindowShouldClose(pWindow)) {
    openglWindow.showFPS();
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    
    texture.bind();

    customShader.use();
    glBindVertexArray(arrayObj);

    /*
    GLfloat time = glfwGetTime();
    GLfloat blueColor = (sin(time) / 2) + 0.05f;
    customShader.setUniform("vertColor",glm::vec4(0.0f,0.0f,blueColor,1.0f));

    glm::vec2 pos;
    pos.x = (cos(time) / 2) + 0.05f;
    pos.y = (sin(time) / 2) + 0.05f;
    customShader.setUniform("positionOffset",pos);*/


    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    //glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);


    glfwSwapBuffers(pWindow);
  }

  //glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1,&arrayObj);
  glDeleteBuffers(1,&vertexObj);
  //glDeleteBuffers(1,&ibo);

  glfwTerminate();
  return 0;
	
}

