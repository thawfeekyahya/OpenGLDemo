#include "MainWindow.h"
#include <iostream>
#include <sstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"


MainWindow::MainWindow() 
{
    
}

GLFWwindow* MainWindow::initOpenGL() {
  
  if(!glfwInit()) {
		std::cerr<<"GLFW Intialization failed"<<std::endl;
		return nullptr;
	}

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

  

  if(fullScreen) {
    GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* pVmode  = glfwGetVideoMode(pMonitor);

    if( pVmode != NULL) {
      window = glfwCreateWindow(pVmode->width,pVmode->height,this->screenTitle,pMonitor,NULL);
    }

  } else {
     window = glfwCreateWindow(this->screenWidth,this->screenHeight,this->screenTitle,NULL,NULL);
  }


  if(window == NULL) {
    std::cout << "Failed to create GLFW window " << std::endl;
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window,handleKeyPress);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK ) {
    std::cerr << "GLEW Failed " << std::endl;
    return nullptr;
  } 

  glClearColor(0.23f,0.38f,0.47f,1.0f);

  return window;
}

void MainWindow::handleKeyPress(GLFWwindow* window,int key,int scancode,int action,int mode){
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
     glfwSetWindowShouldClose(window,GL_TRUE);
  }

  if(key == GLFW_KEY_W && action == GLFW_PRESS) {
    static bool wireframeEnabled = false;
    if(wireframeEnabled) {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
  }
}

void MainWindow::setScreenSize(int pWidth,int pHeight) 
{
    screenWidth = pWidth;
    screenHeight = pHeight;
}


void MainWindow::showFPS() {
   static double previousSeconds = 0.0;
   static int frameCount = 0;
   double elapsedSeconds;
   double currentSeconds = glfwGetTime(); // reutrn number of seconds since GLFW started as a double

   elapsedSeconds = currentSeconds - previousSeconds;

   // limit text update 4 times per second
   if(elapsedSeconds > 0.25) {
     previousSeconds = currentSeconds;
     double fps = (double)frameCount / elapsedSeconds;
     double msPerFrame = 1000.0 / fps;

     std::ostringstream outs;
     outs.precision(3);
     outs << std::fixed
          << screenTitle << "   "
          <<"FPS" << fps << "  "
          <<"Frame Time:" << msPerFrame << " (ms)";
     glfwSetWindowTitle(window,outs.str().c_str());

     frameCount = 0;
   }
   frameCount++;
}
