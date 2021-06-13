#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

const char* APP_TITLE = "Introduction to Modern OpenGL";
const int gWindowWidth=800;
const int gWindowHeight=600;

int main() {

	if(!glfwInit()) {
		std::cerr<<"GLFW Intialization failed"<<std::endl;
		return -1;
	}

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

  GLFWwindow* pWindow = glfwCreateWindow(gWindowWidth,gWindowHeight,APP_TITLE,NULL,NULL);

  if(pWindow == NULL) {
    std::cerr << "Failed to create GLFW window " << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(pWindow);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK ) {
    std::cerr << "GLEW Failed " << std::endl;
  }

  while (!glfwWindowShouldClose(pWindow)) {
    glfwPollEvents();
    glfwSwapBuffers(pWindow);
  }

  glfwTerminate();
  return 0;
}
